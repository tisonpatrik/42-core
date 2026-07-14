/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:39:19 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:47:25 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/state.h"

static char	*join_env_str(t_arena *arena, t_str8 key, t_str8 value)
{
	char	*res;
	size_t	total;

	if (!key.str || !value.str)
		return (NULL);
	total = key.len + 1 + value.len + 1;
	res = ft_arena_push(arena, total);
	if (!res)
		return (NULL);
	ft_memcpy(res, key.str, key.len);
	res[key.len] = '=';
	ft_memcpy(res + key.len + 1, value.str, value.len);
	res[total - 1] = '\0';
	return (res);
}

t_str8	env_get(t_env *env, t_str8 key)
{
	if (!env || !key.str)
		return ((t_str8){NULL, 0});
	while (env)
	{
		if (ft_str8_match(env->key, key))
			return (env->value);
		env = env->next;
	}
	return ((t_str8){NULL, 0});
}

char	**env_to_array(t_shell *shell)
{
	t_env	*tmp;
	char	**array;
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	tmp = shell->env_list;
	while (tmp && ++count)
		tmp = tmp->next;
	array = ft_arena_push(shell->cmd_arena, sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	tmp = shell->env_list;
	while (tmp)
	{
		array[i] = join_env_str(shell->cmd_arena, tmp->key, tmp->value);
		if (!array[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (array[i] = NULL, array);
}
