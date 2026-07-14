/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:57 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:38:01 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	parser_init(t_parse_ctx *ctx, t_arena *arena, t_token *tokens)
{
	ctx->curr = tokens;
	ctx->arena = arena;
	ctx->error = false;
}

t_token	*parser_eat(t_parse_ctx *ctx)
{
	t_token	*tok;

	tok = ctx->curr;
	if (tok)
		ctx->curr = tok->next;
	return (tok);
}

t_token_type	parser_peek(t_parse_ctx *ctx)
{
	if (!ctx->curr)
		return (TOKEN_EOF);
	return (ctx->curr->type);
}

bool	parser_match(t_parse_ctx *ctx, t_token_type type)
{
	if (parser_peek(ctx) == type)
	{
		parser_eat(ctx);
		return (true);
	}
	return (false);
}
