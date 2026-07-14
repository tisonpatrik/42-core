/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:34:57 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 17:01:57 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	env_cmp_wrapper(void *a, void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = (t_env *)a;
	env_b = (t_env *)b;
	return (ft_str8_cmp(env_a->key, env_b->key));
}

static void	print_sorted_export(t_shell *shell)
{
	t_env	**array;
	t_env	*curr;
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	curr = shell->env_list;
	while (curr && ++count)
		curr = curr->next;
	if (count == 0)
		return ;
	array = ft_arena_push(shell->cmd_arena, sizeof(t_env *) * count);
	if (!array)
		return ;
	curr = shell->env_list;
	while (curr)
	{
		array[i++] = curr;
		curr = curr->next;
	}
	ft_heap_sort_ptr((void **)array, count, env_cmp_wrapper);
	print_env_arr(array, count);
}

t_status	handle_append(t_shell *shell, t_str8 arg, char *arg_str,
		char *app_sign)
{
	size_t	key_len;
	t_str8	key;
	t_str8	val;
	t_str8	old;
	t_str8	new_v;

	key_len = app_sign - arg_str;
	key = ft_str8_substr(arg, 0, key_len);
	val = ft_str8_substr(arg, key_len + 2, arg.len - key_len - 2);
	if (!ft_is_valid_identifier(key))
	{
		shell_error("export", arg_str, "not a valid identifier");
		return (FAILURE);
	}
	old = env_get(shell->env_list, key);
	if (old.str)
	{
		new_v = ft_str8_join(shell->cmd_arena, old, val);
		env_set(shell, key, new_v);
	}
	else
		env_set(shell, key, val);
	return (SUCCESS);
}

t_status	handle_assign(t_shell *shell, t_str8 arg, char *arg_str,
		char *eq_sign)
{
	size_t	key_len;
	t_str8	key;
	t_str8	val;

	if (eq_sign)
	{
		key_len = eq_sign - arg_str;
		key = ft_str8_substr(arg, 0, key_len);
		val = ft_str8_substr(arg, key_len + 1, arg.len - key_len - 1);
	}
	else
	{
		key = arg;
		val = (t_str8){NULL, 0};
	}
	if (!ft_is_valid_identifier(key))
	{
		shell_error("export", arg_str, "not a valid identifier");
		return (FAILURE);
	}
	env_set(shell, key, val);
	return (SUCCESS);
}

t_status	ft_export(t_shell *shell, char **args)
{
	int			i;
	t_status	status;
	t_status	ret;

	if (!args[1])
		return (print_sorted_export(shell), SUCCESS);
	i = 0;
	status = SUCCESS;
	while (args[++i])
	{
		ret = process_export_arg(shell, args[i]);
		if (ret == 2)
			return (2);
		if (ret != SUCCESS)
			status = FAILURE;
	}
	return (status);
}
