/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:40:00 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:40:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str8.h"
#include "ft_math.h"
#include "mem.h"

char	*ft_str8_to_cstr(t_arena *arena, t_str8 s)
{
	char	*res;
	size_t	size;

	if (!s.str || !ft_size_add(s.len, 1, &size))
		return (NULL);
	res = ft_arena_push(arena, size);
	if (!res)
		return (NULL);
	ft_memcpy(res, s.str, s.len);
	res[s.len] = '\0';
	return (res);
}

t_str8	ft_str8_join(t_arena *arena, t_str8 s1, t_str8 s2)
{
	t_str8	res;
	size_t	size;

	if ((!s1.str && s1.len != 0) || (!s2.str && s2.len != 0)
		|| !ft_size_add(s1.len, s2.len, &res.len)
		|| !ft_size_add(res.len, 1, &size))
		return ((t_str8){NULL, 0});
	res.str = ft_arena_push(arena, size);
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
	size_t	size;

	if (!s.str || !ft_size_add(s.len, 1, &size))
		return ((t_str8){NULL, 0});
	res.len = s.len;
	res.str = ft_arena_push(arena, size);
	if (!res.str)
		return ((t_str8){NULL, 0});
	if (s.len > 0)
		ft_memcpy(res.str, s.str, s.len);
	res.str[s.len] = '\0';
	return (res);
}
