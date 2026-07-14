/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:34:46 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:34:49 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static bool	should_print_entry(t_env *entry)
{
	if (!entry->value.str)
		return (false);
	return (true);
}

t_status	ft_env(t_shell *shell, char **args)
{
	t_env	*tmp;

	if (args && args[1])
	{
		shell_error("env", args[1], "No such file or directory");
		return (127);
	}
	if (!shell || !shell->env_list)
		return (FAILURE);
	tmp = shell->env_list;
	while (tmp)
	{
		if (should_print_entry(tmp))
		{
			ft_printf("%s=%s\n", (char *)tmp->key.str, (char *)tmp->value.str);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
