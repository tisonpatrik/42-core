/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:23 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:46:42 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	*append_literal_dollar(t_exp_ctx *ctx, char *ptr)
{
	exp_builder_append(ctx->arena, &ctx->builder, ft_str8_from_cstr("$"));
	return (ptr);
}

static char	*process_dollar(t_exp_ctx *ctx, char *cursor)
{
	char	*start;
	char	*end;
	t_str8	val;

	start = cursor + 1;
	if (!*start || ft_isspace(*start))
		return (append_literal_dollar(ctx, start));
	if (*start == '\"' || *start == '\'')
	{
		if (ctx->in_dq)
			append_literal_dollar(ctx, start);
		return (start);
	}
	end = find_var_end(start);
	if (end == start)
		return (append_literal_dollar(ctx, start));
	val = exp_get_var_val(ctx, ft_str8_create((uint8_t *)start, end - start));
	if (ctx->in_dq)
		exp_builder_append(ctx->arena, &ctx->builder, val);
	else
		process_dollar_split(ctx, val);
	return (end);
}

static char	*handle_quotes(t_exp_ctx *ctx, char *cursor)
{
	if (*cursor == '\'' && !ctx->in_dq)
	{
		ctx->in_sq = !ctx->in_sq;
		ctx->was_quoted = true;
		return (cursor + 1);
	}
	if (*cursor == '\"' && !ctx->in_sq)
	{
		ctx->in_dq = !ctx->in_dq;
		ctx->was_quoted = true;
		return (cursor + 1);
	}
	return (NULL);
}

static bool	try_process_special(t_exp_ctx *ctx, char **cursor, char **anchor)
{
	char	*next;

	next = handle_quotes(ctx, *cursor);
	if (next)
	{
		flush_segment(ctx, *anchor, *cursor);
		*anchor = next;
		*cursor = next;
		return (true);
	}
	if (**cursor == '$' && !ctx->in_sq)
	{
		flush_segment(ctx, *anchor, *cursor);
		*cursor = process_dollar(ctx, *cursor);
		*anchor = *cursor;
		return (true);
	}
	return (false);
}

t_str8_list	expand_word(t_exp_ctx *ctx, t_str8 word)
{
	char	*cursor;
	char	*anchor;
	char	*end;

	cursor = (char *)word.str;
	anchor = cursor;
	end = cursor + word.len;
	while (cursor < end)
	{
		if (!try_process_special(ctx, &cursor, &anchor))
			cursor++;
	}
	flush_segment(ctx, anchor, cursor);
	if (ctx->builder.total_size > 0 || ctx->was_quoted)
	{
		exp_builder_append(ctx->arena, &ctx->expanded_words,
			exp_builder_flatten(ctx->arena, &ctx->builder));
	}
	return (ctx->expanded_words);
}
