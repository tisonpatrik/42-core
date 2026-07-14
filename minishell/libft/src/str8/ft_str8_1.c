/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:59:59 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:03:33 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/str8.h"

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

	if (start >= s.len)
	{
		res.str = s.str + s.len;
		res.len = 0;
		return (res);
	}
	if (start + len > s.len)
		len = s.len - start;
	res.str = s.str + start;
	res.len = len;
	return (res);
}
