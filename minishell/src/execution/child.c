/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:35:28 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:52:03 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

static void	exit_child(t_shell *shell, int code)
{
	ft_arena_destroy(shell->life_arena);
	ft_arena_destroy(shell->cmd_arena);
	exit(code);
}

static void	check_binary_path(t_shell *shell, char *path, char *cmd)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		shell_error(path, NULL, "Is a directory");
		exit_child(shell, 126);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		shell_perror(NULL, path);
		exit_child(shell, 126);
	}
	else if (access(path, F_OK) != 0 && ft_strchr(cmd, '/'))
	{
		shell_perror(NULL, path);
		exit_child(shell, 127);
	}
}

static void	execute_binary(t_shell *shell, char **argv)
{
	char	*path;

	path = exec_find_path(shell, argv[0]);
	if (!path)
	{
		shell_error(argv[0], NULL, "command not found");
		exit_child(shell, 127);
	}
	check_binary_path(shell, path, argv[0]);
	env_set(shell, ft_str8_from_cstr("_"), ft_str8_from_cstr(path));
	execve(path, argv, env_to_array(shell));
	shell_perror(NULL, path);
	exit_child(shell, 126);
}

void	exec_child_routine(t_shell *shell, t_ast_node *node)
{
	char			**argv;
	t_builtin_id	id;

	setup_signals_child();
	if (!exec_handle_redirs(shell->cmd_arena, node->redirs))
		exit_child(shell, 1);
	argv = exec_args_to_array(shell->cmd_arena, node->args);
	if (!argv || !argv[0])
		exit_child(shell, 0);
	id = identify_builtin(argv[0]);
	if (id != BUILTIN_NONE)
		exit_child(shell, run_builtin(shell, id, argv));
	execute_binary(shell, argv);
}
