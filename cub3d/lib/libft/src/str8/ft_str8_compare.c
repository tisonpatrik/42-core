/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_compare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:39:57 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:39:58 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str8.h"
#include "str.h"

bool	ft_str8_match(t_str8 a, t_str8 b)
{
	size_t	i;

	if (a.len != b.len)
		return (false);
	i = 0;
	while (i < a.len)
	{
		if (a.str[i] != b.str[i])
			return (false);
		i++;
	}
	return (true);
}

int	ft_str8_cmp(t_str8 a, t_str8 b)
{
	size_t	min_len;
	int		res;

	if (a.len < b.len)
		min_len = a.len;
	else
		min_len = b.len;
	res = ft_strncmp((const char *)a.str, (const char *)b.str, min_len);
	if (res == 0)
	{
		if (a.len < b.len)
			return (-1);
		if (a.len > b.len)
			return (1);
		return (0);
	}
	return (res);
}
