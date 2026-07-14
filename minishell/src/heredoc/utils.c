/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:19 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:37:27 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/heredoc.h"

/*
** Wrapper for write. Returns false, if write fall.
*/
bool	hdoc_write(int fd, t_str8 s)
{
	if (s.len == 0)
		return (true);
	if (write(fd, s.str, s.len) == -1)
	{
		shell_perror("heredoc", "write error");
		return (false);
	}
	return (true);
}

t_str8	heredoc_generate_name(t_arena *arena, int id)
{
	char	*num;
	t_str8	res;

	num = ft_itoa(id);
	if (!num)
		return ((t_str8){NULL, 0});
	res = ft_str8_join(arena, ft_str8_from_cstr("/tmp/.heredoc_"),
			ft_str8_from_cstr(num));
	free(num);
	return (res);
}

static void	copy_quoted_part(t_str8 raw, char *buf, size_t *r, size_t *w)
{
	char	quote;

	quote = raw.str[(*r)++];
	while (*r < raw.len && raw.str[*r] != quote)
	{
		buf[(*w)++] = raw.str[(*r)++];
	}
	if (*r < raw.len)
		(*r)++;
}

t_str8	heredoc_strip_quotes(t_arena *arena, t_str8 raw, bool *expand)
{
	char	*buf;
	size_t	r;
	size_t	w;

	buf = ft_arena_push(arena, raw.len + 1);
	if (!buf)
		return ((t_str8){NULL, 0});
	*expand = true;
	r = 0;
	w = 0;
	while (r < raw.len)
	{
		if (raw.str[r] == '\'' || raw.str[r] == '\"')
		{
			*expand = false;
			copy_quoted_part(raw, buf, &r, &w);
		}
		else
			buf[w++] = raw.str[r++];
	}
	buf[w] = '\0';
	return ((t_str8){(uint8_t *)buf, w});
}
