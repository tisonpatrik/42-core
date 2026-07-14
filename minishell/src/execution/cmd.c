/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:35:34 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:50:31 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	backup_fds(int *bkp)
{
	bkp[0] = dup(STDIN_FILENO);
	bkp[1] = dup(STDOUT_FILENO);
	bkp[2] = dup(STDERR_FILENO);
}

static void	restore_fds(int *bkp)
{
	dup2(bkp[0], STDIN_FILENO);
	dup2(bkp[1], STDOUT_FILENO);
	dup2(bkp[2], STDERR_FILENO);
	close(bkp[0]);
	close(bkp[1]);
	close(bkp[2]);
}

static int	run_isolated_builtin(t_shell *shell, t_builtin_id id,
		t_ast_node *node)
{
	int		bkp[3];
	int		ret;
	char	**argv;

	backup_fds(bkp);
	if (exec_handle_redirs(shell->cmd_arena, node->redirs))
	{
		argv = exec_args_to_array(shell->cmd_arena, node->args);
		ret = run_builtin(shell, id, argv);
	}
	else
		ret = 1;
	restore_fds(bkp);
	return (ret);
}

static int	wait_for_child(pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		return (128 + sig);
	}
	return (status);
}

int	exec_simple_cmd(t_shell *shell, t_ast_node *node)
{
	t_builtin_id	id;
	pid_t			pid;
	int				bkp[3];

	if (!node->args || !node->args[0].str)
	{
		backup_fds(bkp);
		if (!exec_handle_redirs(shell->cmd_arena, node->redirs))
			return (restore_fds(bkp), 1);
		restore_fds(bkp);
		return (0);
	}
	id = identify_builtin((char *)node->args[0].str);
	if (id == BUILTIN_CD || id == BUILTIN_EXPORT || id == BUILTIN_UNSET
		|| id == BUILTIN_EXIT)
		return (run_isolated_builtin(shell, id, node));
	setup_signals_blocking();
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		exec_child_routine(shell, node);
	id = wait_for_child(pid);
	setup_signals_interactive();
	return (id);
}
