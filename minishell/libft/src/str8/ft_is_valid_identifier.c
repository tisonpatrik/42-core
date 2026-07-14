/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_identifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:03:43 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:56:41 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/str8.h"

bool	ft_is_valid_identifier(t_str8 key)
{
	size_t	i;

	if (!key.str || key.len == 0)
		return (false);
	if (!ft_isalpha(key.str[0]) && key.str[0] != '_')
		return (false);
	i = 1;
	while (i < key.len)
	{
		if (!ft_isalnum(key.str[i]) && key.str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
