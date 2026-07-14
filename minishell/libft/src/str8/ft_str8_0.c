/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:01:38 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:03:21 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/str8.h"

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

char	*str8_to_cstr(t_arena *arena, t_str8 s)
{
	char	*res;

	if (!s.str)
		return (NULL);
	res = ft_arena_push(arena, s.len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s.str, s.len);
	res[s.len] = '\0';
	return (res);
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

t_str8	ft_str8_join(t_arena *arena, t_str8 s1, t_str8 s2)
{
	t_str8	res;

	res.len = s1.len + s2.len;
	res.str = ft_arena_push(arena, res.len + 1);
	if (!res.str)
		return ((t_str8){NULL, 0});
	if (s1.len > 0)
		ft_memcpy(res.str, s1.str, s1.len);
	if (s2.len > 0)
		ft_memcpy(res.str + s1.len, s2.str, s2.len);
	res.str[res.len] = '\0';
	return (res);
}

t_str8	ft_str8_dup(t_arena *arena, t_str8 s)
{
	t_str8	res;

	res.len = s.len;
	res.str = ft_arena_push(arena, s.len + 1);
	if (!res.str)
		return ((t_str8){NULL, 0});
	if (s.len > 0)
		ft_memcpy(res.str, s.str, s.len);
	res.str[s.len] = '\0';
	return (res);
}
