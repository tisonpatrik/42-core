/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:39:27 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:49:23 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/state.h"

static t_str8	str8_dup_life(t_arena *arena, t_str8 s)
{
	uint8_t	*dest;

	if (!s.str)
		return ((t_str8){NULL, 0});
	dest = ft_arena_push(arena, s.len + 1);
	if (!dest)
		return ((t_str8){NULL, 0});
	ft_memcpy(dest, s.str, s.len);
	dest[s.len] = '\0';
	return ((t_str8){dest, s.len});
}

static t_env	*env_find_node(t_env *head, t_str8 key)
{
	if (!key.str)
		return (NULL);
	while (head)
	{
		if (ft_str8_match(head->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_status	env_set(t_shell *shell, t_str8 key, t_str8 value)
{
	t_env	*node;
	t_str8	new_key;
	t_str8	new_val;

	node = env_find_node(shell->env_list, key);
	if (node)
	{
		if (value.str)
			node->value = str8_dup_life(shell->life_arena, value);
		else
			node->value = (t_str8){NULL, 0};
		return (SUCCESS);
	}
	new_key = str8_dup_life(shell->life_arena, key);
	new_val = (t_str8){NULL, 0};
	if (value.str)
		new_val = str8_dup_life(shell->life_arena, value);
	if (!new_key.str || (value.str && !new_val.str))
		return (FAILURE);
	return (env_add_back(&shell->env_list, env_new(shell->life_arena, new_key,
				new_val)));
}

t_status	env_remove(t_shell *shell, t_str8 key)
{
	t_env	*curr;
	t_env	*prev;

	if (!shell->env_list || !key.str)
		return (SUCCESS);
	curr = shell->env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_str8_match(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			return (SUCCESS);
		}
		prev = curr;
		curr = curr->next;
	}
	return (SUCCESS);
}
