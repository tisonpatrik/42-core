/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:48:57 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:50:13 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/state.h"

t_env	*env_new(t_arena *arena, t_str8 key, t_str8 value)
{
	t_env	*node;

	node = ft_arena_push(arena, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_status	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*tmp;

	if (!new_node)
		return (FAILURE);
	if (!*head)
	{
		*head = new_node;
		return (SUCCESS);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (SUCCESS);
}
