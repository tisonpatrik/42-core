/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:38:31 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:38:34 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

bool	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_INPUT || type == TOKEN_REDIRECT_OUTPUT
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_REDIRECT_HEREDOC
		|| type == TOKEN_REDIRECT_ERR);
}

bool	parse_redir(t_parse_ctx *ctx, t_ast_node *node)
{
	t_token	*op;
	t_token	*file;
	t_token	*new_redir;

	op = parser_eat(ctx);
	if (parser_peek(ctx) != TOKEN_WORD)
	{
		shell_error("parser", NULL, "syntax error near unexpected token");
		ctx->error = true;
		return (false);
	}
	file = parser_eat(ctx);
	new_redir = token_create(ctx->arena, file->value, op->type);
	if (!new_redir)
	{
		ctx->error = true;
		return (false);
	}
	token_add_back(&node->redirs, new_redir);
	return (true);
}
