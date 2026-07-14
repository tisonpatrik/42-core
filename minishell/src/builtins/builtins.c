/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:34:26 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:34:30 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_builtin_id	identify_builtin(char *cmd)
{
	if (!cmd)
		return (BUILTIN_NONE);
	if (strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	if (strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	if (strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	if (strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	if (strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	if (strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	if (strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);
}

t_status	run_builtin(t_shell *shell, t_builtin_id id, char **args)
{
	if (id == BUILTIN_ECHO)
		return (ft_echo(args));
	if (id == BUILTIN_CD)
		return (ft_cd(shell, args));
	if (id == BUILTIN_PWD)
		return (ft_pwd());
	if (id == BUILTIN_EXPORT)
		return (ft_export(shell, args));
	if (id == BUILTIN_UNSET)
		return (ft_unset(shell, args));
	if (id == BUILTIN_ENV)
		return (ft_env(shell, args));
	if (id == BUILTIN_EXIT)
		return (ft_exit(shell, args));
	return (ERR_NO_CMD);
}
