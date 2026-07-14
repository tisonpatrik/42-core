/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:20:23 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:27:28 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	print_env_arr(t_env **arr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (!ft_str8_match(arr[i]->key, ft_str8_from_cstr("_")))
		{
			ft_printf("declare -x %s", (char *)arr[i]->key.str);
			if (arr[i]->value.str)
				ft_printf("=\"%s\"", (char *)arr[i]->value.str);
			ft_printf("\n");
		}
		i++;
	}
}

t_status	process_export_arg(t_shell *shell, char *arg_str)
{
	t_str8	arg;
	char	*app_sign;
	char	*eq_sign;

	if (arg_str[0] == '-' && arg_str[1] != '\0')
		return (shell_error("export", arg_str, "invalid option"), 2);
	arg = ft_str8_from_cstr(arg_str);
	app_sign = ft_strnstr(arg_str, "+=", arg.len);
	eq_sign = ft_strchr(arg_str, '=');
	if (app_sign && (!eq_sign || app_sign < eq_sign))
		return (handle_append(shell, arg, arg_str, app_sign));
	return (handle_assign(shell, arg, arg_str, eq_sign));
}
