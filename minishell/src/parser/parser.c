/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:38:40 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:38:41 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static bool	pre_validation(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (tokens->type == TOKEN_PIPE)
	{
		shell_error("parser", NULL, "syntax error near unexpected token `|'");
		return (false);
	}
	return (true);
}

t_ast_node	*parser_build_ast(t_arena *arena, t_token *tokens)
{
	t_parse_ctx	ctx;
	t_ast_node	*ast;

	if (!pre_validation(tokens))
		return (NULL);
	parser_init(&ctx, arena, tokens);
	ast = parse_job(&ctx);
	if (ctx.error)
		return (NULL);
	if (parser_peek(&ctx) != TOKEN_EOF)
	{
		shell_error("parser", NULL, "syntax error: unexpected token");
		return (NULL);
	}
	return (ast);
}
