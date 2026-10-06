#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_command(char **cmd, int input_fd, int fds[2])
{
	if (fds[0] != -1)
		close(fds[0]);
	if (input_fd != -1 && input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit(1);
		close(input_fd);
	}
	if (fds[1] != -1 && fds[1] != STDOUT_FILENO)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit(1);
		close(fds[1]);
	}
	execvp(cmd[0], cmd);
	exit(1);
}

static int	wait_children(pid_t pids[], int children, int result)
{
	int		remaining;
	int		status;
	int		i;
	pid_t	pid;

	remaining = children;
	while (remaining > 0)
	{
		pid = wait(&status);
		if (pid == -1)
		{
			if (errno == EINTR)
				continue ;
			return (1);
		}
		i = 0;
		while (i < children && pids[i] != pid)
			i++;
		if (i == children)
			continue ;
		pids[i] = -1;
		remaining--;
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			result = 1;
	}
	return (result);
}

static int	execute_pipeline(char **cmds[], pid_t pids[])
{
	int		fds[2];
	int		input_fd;
	int		children;
	int		result;
	pid_t	pid;

	input_fd = -1;
	children = 0;
	result = 0;
	while (*cmds)
	{
		fds[0] = -1;
		fds[1] = -1;
		if (cmds[1] && pipe(fds) == -1)
		{
			result = 1;
			break ;
		}
		pid = fork();
		if (pid == -1)
		{
			if (fds[0] != -1)
				close(fds[0]);
			if (fds[1] != -1)
				close(fds[1]);
			result = 1;
			break ;
		}
		if (pid == 0)
			execute_command(*cmds, input_fd, fds);
		pids[children++] = pid;
		if (input_fd != -1)
			close(input_fd);
		if (fds[1] != -1)
			close(fds[1]);
		input_fd = fds[0];
		cmds++;
	}
	if (input_fd != -1)
		close(input_fd);
	return (wait_children(pids, children, result));
}

int	picoshell(char **cmds[])
{
	int	count;

	if (!cmds)
		return (1);
	count = 0;
	while (cmds[count])
		count++;
	if (count == 0)
		return (0);
	{
		pid_t	pids[count];

		return (execute_pipeline(cmds, pids));
	}
}
