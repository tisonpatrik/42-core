/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:40:06 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:40:07 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str8.h"
#include "core.h"
#include "mem.h"

t_str8	ft_str8_trim(t_str8 s)
{
	t_str8	res;
	size_t	start;
	size_t	end;

	if (!s.str)
		return ((t_str8){NULL, 0});
	start = 0;
	while (start < s.len && ft_isspace(s.str[start]))
		start++;
	end = s.len;
	while (end > start && ft_isspace(s.str[end - 1]))
		end--;
	res.str = s.str + start;
	res.len = end - start;
	return (res);
}

bool	ft_str8_next_token(t_str8 *cursor, uint8_t delimiter, t_str8 *token)
{
	size_t	i;

	if (!cursor || !token || !cursor->str)
		return (false);
	i = 0;
	while (i < cursor->len && cursor->str[i] != delimiter)
		i++;
	*token = (t_str8){cursor->str, i};
	if (i < cursor->len)
		*cursor = (t_str8){cursor->str + i + 1, cursor->len - i - 1};
	else
		*cursor = (t_str8){NULL, 0};
	return (true);
}

static void	ft_str8_list_push(t_str8_list *list, t_str8_node *node)
{
	if (!list->first)
		list->first = node;
	else
		list->last->next = node;
	list->last = node;
	list->count++;
	list->total_size += node->string.len;
}

static bool	push_substring(t_arena *arena, t_str8_list *list,
	t_arena_temp scratch, t_str8 substring)
{
	t_str8_node	*node;

	node = ft_arena_push(arena, sizeof(t_str8_node));
	if (!node)
	{
		ft_scratch_end(scratch);
		return (false);
	}
	node->string = substring;
	ft_str8_list_push(list, node);
	return (true);
}

t_str8_list	ft_str8_split(t_arena *arena, t_str8 s, uint8_t delimiter)
{
	t_str8_list		list;
	t_arena_temp	scratch;
	size_t			i;
	size_t			start;

	scratch = ft_scratch_begin(arena);
	ft_memset(&list, 0, sizeof(t_str8_list));
	list.valid = true;
	i = 0;
	start = 0;
	while (i <= s.len)
	{
		if (i == s.len || s.str[i] == delimiter)
		{
			if (i > start && !push_substring(arena, &list, scratch,
					(t_str8){s.str + start, i - start}))
				return ((t_str8_list){0});
			start = i + 1;
		}
		i++;
	}
	return (list);
}
