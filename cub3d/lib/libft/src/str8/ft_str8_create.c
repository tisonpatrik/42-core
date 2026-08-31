/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:40:03 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:40:04 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str8.h"
#include "str.h"

t_str8	ft_str8_create(uint8_t *str, size_t len)
{
	return ((t_str8){str, len});
}

t_str8	ft_str8_from_cstr(const char *cstr)
{
	t_str8	res;

	res.str = (uint8_t *)cstr;
	res.len = 0;
	if (cstr)
		res.len = ft_strlen(cstr);
	return (res);
}

t_str8	ft_str8_substr(t_str8 s, size_t start, size_t len)
{
	t_str8	res;

	if (!s.str)
		return ((t_str8){NULL, 0});
	if (start >= s.len)
	{
		res.str = s.str + s.len;
		res.len = 0;
		return (res);
	}
	if (len > s.len - start)
		len = s.len - start;
	res.str = s.str + start;
	res.len = len;
	return (res);
}
