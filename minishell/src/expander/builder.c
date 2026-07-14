/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:16 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:36:20 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	exp_builder_append(t_arena *arena, t_str8_list *list, t_str8 str)
{
	t_str8_node	*node;

	if (!str.str)
		return ;
	node = ft_arena_push(arena, sizeof(t_str8_node));
	if (!node)
		return ;
	node->string = str;
	node->next = NULL;
	if (!list->first)
		list->first = node;
	else
		list->last->next = node;
	list->last = node;
	list->total_size += str.len;
}

t_str8	exp_builder_flatten(t_arena *arena, t_str8_list *list)
{
	uint8_t		*dest;
	size_t		offset;
	t_str8_node	*curr;

	if (list->total_size == 0)
		return (ft_str8_from_cstr(""));
	dest = ft_arena_push(arena, list->total_size + 1);
	if (!dest)
		return ((t_str8){NULL, 0});
	offset = 0;
	curr = list->first;
	while (curr)
	{
		ft_memcpy(dest + offset, curr->string.str, curr->string.len);
		offset += curr->string.len;
		curr = curr->next;
	}
	dest[offset] = '\0';
	return ((t_str8){dest, list->total_size});
}
