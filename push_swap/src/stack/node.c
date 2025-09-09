/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/09 18:49:13 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"
#include <stdlib.h>

t_node	*create_node(int content)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	get_content(t_node *node)
{
	if (!node)
		return (0);
	return (node->content);
}

t_node	*get_next(t_node *node)
{
	if (!node)
		return (NULL);
	return (node->next);
}

t_node	*get_prev(t_node *node)
{
	if (!node)
		return (NULL);
	return (node->prev);
}
