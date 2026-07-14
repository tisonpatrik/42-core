/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:35:48 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:50:10 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	redir_pipe(int *pfd, bool is_left)
{
	if (is_left)
	{
		close(pfd[0]);
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
		{
			shell_perror("dup2", NULL);
			close(pfd[1]);
			exit(1);
		}
		close(pfd[1]);
	}
	else
	{
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
		{
			shell_perror("dup2", NULL);
			close(pfd[0]);
			exit(1);
		}
		close(pfd[0]);
	}
}

static pid_t	spawn_left_child(t_shell *shell, t_ast_node *node, int *pfd)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
	{
		shell_perror("fork", NULL);
		return (-1);
	}
	if (pid == 0)
	{
		redir_pipe(pfd, true);
		ret = executor(shell, node);
		ft_arena_destroy(shell->life_arena);
		ft_arena_destroy(shell->cmd_arena);
		exit(ret);
	}
	return (pid);
}

static pid_t	spawn_right_child(t_shell *shell, t_ast_node *node, int *pfd)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == -1)
	{
		shell_perror("fork", NULL);
		return (-1);
	}
	if (pid == 0)
	{
		redir_pipe(pfd, false);
		ret = executor(shell, node);
		ft_arena_destroy(shell->life_arena);
		ft_arena_destroy(shell->cmd_arena);
		exit(ret);
	}
	return (pid);
}

static int	wait_pipeline(pid_t pid_l, pid_t pid_r, int *pfd)
{
	int	status;
	int	exit_code;
	int	sig;

	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid_l, NULL, 0);
	waitpid(pid_r, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		exit_code = 128 + sig;
	}
	else
		exit_code = 1;
	return (exit_code);
}

int	exec_pipe(t_shell *shell, t_ast_node *node)
{
	int		pfd[2];
	pid_t	pid_l;
	pid_t	pid_r;
	int		ret;

	if (pipe(pfd) == -1)
		return (shell_perror("pipe", NULL), 1);
	setup_signals_blocking();
	pid_l = spawn_left_child(shell, node->left, pfd);
	if (pid_l == -1)
		return (close(pfd[0]), close(pfd[1]), 1);
	pid_r = spawn_right_child(shell, node->right, pfd);
	if (pid_r == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		waitpid(pid_l, NULL, 0);
		return (1);
	}
	ret = wait_pipeline(pid_l, pid_r, pfd);
	setup_signals_interactive();
	return (ret);
}
