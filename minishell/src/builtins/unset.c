/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:35:10 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:35:16 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_status	ft_unset(t_shell *shell, char **args)
{
	int			i;
	t_str8		key;
	t_status	status;

	i = 1;
	status = SUCCESS;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] != '\0')
		{
			shell_error("unset", args[i], "invalid option");
			return (2);
		}
		key = ft_str8_from_cstr(args[i]);
		if (!ft_is_valid_identifier(key))
		{
			shell_error("unset", args[i], "not a valid identifier");
			status = FAILURE;
		}
		else
			env_remove(shell, key);
		i++;
	}
	return (status);
}
