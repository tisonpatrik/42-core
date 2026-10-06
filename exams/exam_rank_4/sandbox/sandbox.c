#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif

#include <stdbool.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile sig_atomic_t	g_child = -1;
static volatile sig_atomic_t	g_timeout;
static volatile sig_atomic_t	g_reaped;
static volatile sig_atomic_t	g_status;

static void	handle_timeout(int signal_number)
{
	int		saved_errno;
	int		status;
	pid_t	result;

	(void)signal_number;
	saved_errno = errno;
	if (g_child > 0)
	{
		/* Check ownership before killing: the main wait may have just reaped. */
		result = waitpid(g_child, &status, WNOHANG);
		if (result > 0)
		{
			g_status = status;
			g_reaped = 1;
		}
		else if (result == 0)
		{
			g_timeout = 1;
			if (kill(g_child, SIGKILL) == -1 && errno != ESRCH)
				g_timeout = -1;
		}
		else if (errno != ECHILD)
			g_timeout = -1;
	}
	errno = saved_errno;
}

static int	kill_and_reap(pid_t child)
{
	pid_t	result;

	if (kill(child, SIGKILL) == -1 && errno != ESRCH)
		return (-1);
	result = waitpid(child, NULL, 0);
	while (result == -1 && errno == EINTR)
		result = waitpid(child, NULL, 0);
	if (result == -1 && errno != ECHILD)
		return (-1);
	return (0);
}

static int	report_result(int status, unsigned int timeout, bool verbose)
{
	if (g_timeout)
	{
		if (verbose)
			printf("Bad function: timed out after %u seconds\n", timeout);
		return (0);
	}
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		if (verbose)
			printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
	}
	else if (verbose && WIFSIGNALED(status))
		printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
	else if (verbose && WIFSTOPPED(status))
		printf("Bad function: %s\n", strsignal(WSTOPSIG(status)));
	return (0);
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction	action;
	struct sigaction	old_action;
	pid_t				child;
	pid_t				result;
	int					status;
	int					error;

	if (!f)
		return (-1);
	action.sa_handler = handle_timeout;
	action.sa_flags = 0;
	if (sigfillset(&action.sa_mask) == -1)
		return (-1);
	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
	{
		f();
		exit(0);
	}
	if (sigaction(SIGALRM, &action, &old_action) == -1)
	{
		kill_and_reap(child);
		return (-1);
	}
	g_child = child;
	g_timeout = 0;
	g_reaped = 0;
	alarm(timeout);
	result = waitpid(child, &status, WUNTRACED);
	while (result == -1 && errno == EINTR && g_timeout != -1)
		result = waitpid(child, &status, WUNTRACED);
	alarm(0);
	g_child = -1;
	error = 0;
	if (g_reaped)
	{
		status = g_status;
		result = child;
	}
	if (result == -1)
	{
		if (errno != ECHILD)
			kill_and_reap(child);
		error = 1;
	}
	else if (WIFSTOPPED(status) && kill_and_reap(child) == -1)
		error = 1;
	if (sigaction(SIGALRM, &old_action, NULL) == -1 || g_timeout == -1)
		error = 1;
	if (error)
		return (-1);
	return (report_result(status, timeout, verbose));
}
