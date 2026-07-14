/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:31 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:48:06 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static bool	lexer_skip_whitespace(t_lex_ctx *ctx)
{
	while (ctx->i < ctx->input.len && ft_isspace(ctx->input.str[ctx->i]))
		ctx->i++;
	return (ctx->i >= ctx->input.len);
}

static bool	lexer_append_token(t_lex_ctx *ctx, size_t len, t_token_type type)
{
	t_str8	val;
	t_token	*new_tok;

	val = ft_str8_substr(ctx->input, ctx->i, len);
	new_tok = token_create(ctx->arena, val, type);
	if (!new_tok)
		return (false);
	if (ctx->last)
	{
		ctx->last->next = new_tok;
		ctx->last = new_tok;
	}
	else
	{
		ctx->head = new_tok;
		ctx->last = new_tok;
	}
	return (true);
}

static bool	lexer_process_step(t_lex_ctx *ctx)
{
	t_token_type	type;
	size_t			len;

	len = 0;
	type = scan_token_type((char *)ctx->input.str + ctx->i, &len);
	if (type == TOKEN_ERROR)
	{
		shell_error("lexer", NULL,
			"unexpected EOF while looking for matching quote");
		return (false);
	}
	if (!lexer_append_token(ctx, len, type))
		return (false);
	ctx->i += len;
	return (true);
}

t_token	*lexer_build_token_list(t_arena *arena, char *line)
{
	t_lex_ctx	ctx;

	ctx.arena = arena;
	ctx.head = NULL;
	ctx.last = NULL;
	ctx.input = ft_str8_from_cstr(line);
	ctx.i = 0;
	while (ctx.i < ctx.input.len)
	{
		if (lexer_skip_whitespace(&ctx))
			break ;
		if (!lexer_process_step(&ctx))
			return (NULL);
	}
	lexer_append_token(&ctx, 0, TOKEN_EOF);
	return (ctx.head);
}
