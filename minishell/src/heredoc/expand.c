/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:43 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 13:14:27 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/heredoc.h"

static void	write_var(t_hdoc_ctx *ctx, t_str8 key)
{
	t_str8	val;

	if (ft_str8_match(key, ft_str8_from_cstr("?")))
	{
		write_exit_code(ctx);
		return ;
	}
	val = env_get(ctx->env_list, key);
	if (val.str)
		hdoc_write(ctx->fd, val);
}

static char	*get_var_end(char *start)
{
	if (*start == '?')
		return (start + 1);
	if (ft_isdigit(*start))
		return (start + 1);
	while (*start && (ft_isalnum(*start) || *start == '_'))
		start++;
	return (start);
}

static void	write_plain_text(int fd, char **cursor)
{
	char	*dollar;

	dollar = ft_strchr(*cursor, '$');
	if (dollar)
	{
		hdoc_write(fd, ft_str8_create((uint8_t *)*cursor, dollar - *cursor));
		*cursor = dollar;
	}
	else
	{
		hdoc_write(fd, ft_str8_from_cstr(*cursor));
		*cursor += ft_strlen(*cursor);
	}
}

static void	handle_dollar_expansion(t_hdoc_ctx *ctx, char **cursor)
{
	char	*end;

	end = get_var_end(*cursor + 1);
	if (end == *cursor + 1)
	{
		hdoc_write(ctx->fd, ft_str8_from_cstr("$"));
		*cursor = *cursor + 1;
	}
	else
	{
		write_var(ctx, ft_str8_create((uint8_t *)(*cursor + 1), end - (*cursor
					+ 1)));
		*cursor = end;
	}
}

void	heredoc_write_expanded(t_hdoc_ctx *ctx, char *line)
{
	char	*cursor;

	cursor = line;
	while (*cursor)
	{
		if (*cursor == '$')
			handle_dollar_expansion(ctx, &cursor);
		else
			write_plain_text(ctx->fd, &cursor);
	}
	hdoc_write(ctx->fd, ft_str8_from_cstr("\n"));
}
