/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:35:42 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:35:46 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

int	executor(t_shell *shell, t_ast_node *node)
{
	if (!node)
		return (shell->exit_code);
	if (node->type == NODE_PIPE)
		return (exec_pipe(shell, node));
	if (node->type == NODE_COMMAND)
		return (exec_simple_cmd(shell, node));
	return (0);
}
