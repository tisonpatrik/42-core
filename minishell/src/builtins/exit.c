/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:34:51 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:27:37 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_status	ft_exit(t_shell *shell, char **args)
{
	long long	exit_code;
	bool		error;

	exit_code = shell->exit_code;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1])
	{
		exit_code = ft_atoll_safe(args[1], &error);
		if (error)
		{
			shell_error("exit", args[1], "numeric argument required");
			exit_code = 2;
		}
		else if (args[2])
		{
			shell_error("exit", NULL, "too many arguments");
			return (1);
		}
	}
	ft_arena_destroy(shell->life_arena);
	ft_arena_destroy(shell->cmd_arena);
	exit((unsigned char)exit_code);
}
