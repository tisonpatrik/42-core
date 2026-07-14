/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:40:01 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:53:47 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/state.h"

static void	increment_shlvl(t_shell *shell)
{
	t_str8	key;
	t_str8	val;
	int		lvl;
	bool	error;
	char	*new_str;

	key = ft_str8_from_cstr("SHLVL");
	val = env_get(shell->env_list, key);
	error = false;
	lvl = 1;
	if (val.str)
	{
		lvl = ft_strtoi((const char *)val.str, &error) + 1;
		if (error)
			lvl = 1;
	}
	if (lvl < 0)
		lvl = 0;
	new_str = ft_itoa(lvl);
	if (new_str)
	{
		env_set(shell, key, ft_str8_from_cstr(new_str));
		free(new_str);
	}
}

static t_status	parse_and_add(t_shell *shell, char *env_str)
{
	t_str8	full_str;
	t_str8	key;
	t_str8	value;
	char	*equal_sign;
	size_t	key_len;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
		return (SUCCESS);
	full_str = ft_str8_from_cstr(env_str);
	key_len = equal_sign - env_str;
	key = ft_str8_substr(full_str, 0, key_len);
	value = ft_str8_substr(full_str, key_len + 1, full_str.len - key_len - 1);
	return (env_set(shell, key, value));
}

t_status	env_init(t_shell *shell, char **envp)
{
	int	i;

	shell->env_list = NULL;
	i = 0;
	if (!envp)
		return (SUCCESS);
	while (envp[i])
	{
		if (parse_and_add(shell, envp[i]) != SUCCESS)
			return (FAILURE);
		i++;
	}
	increment_shlvl(shell);
	return (SUCCESS);
}
