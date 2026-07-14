/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:39:00 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:39:04 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_status	shell_init(t_shell *shell, char **envp)
{
	shell->life_arena = ft_arena_create(LIFE_ARENA_SIZE);
	shell->cmd_arena = ft_arena_create(CMD_ARENA_SIZE);
	if (!shell->life_arena || !shell->cmd_arena)
		return (FAILURE);
	shell->exit_code = 0;
	if (env_init(shell, envp) != SUCCESS)
		return (FAILURE);
	setup_signals_interactive();
	return (SUCCESS);
}

void	shell_cleanup(t_shell *shell)
{
	if (shell->life_arena)
		ft_arena_destroy(shell->life_arena);
	if (shell->cmd_arena)
		ft_arena_destroy(shell->cmd_arena);
	rl_clear_history();
}
