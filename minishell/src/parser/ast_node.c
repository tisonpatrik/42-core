/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:51 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:37:55 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_ast_node	*ast_node_create(t_arena *arena, t_node_type type)
{
	t_ast_node	*node;

	node = ft_arena_push(arena, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirs = NULL;
	node->path = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

bool	ast_node_init_args(t_arena *arena, t_ast_node *node, int count)
{
	node->args = ft_arena_push(arena, sizeof(t_str8) * (count + 1));
	if (!node->args)
		return (false);
	node->args[count] = (t_str8){NULL, 0};
	return (true);
}
