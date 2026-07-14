/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:38:28 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:38:29 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static t_ast_node	*parse_pipe_sequence(t_parse_ctx *ctx, t_ast_node *left)
{
	t_ast_node	*pipe_node;
	t_ast_node	*right;

	if (parser_peek(ctx) == TOKEN_EOF)
	{
		shell_error("parser", NULL, "syntax error near unexpected token `|'");
		ctx->error = true;
		return (NULL);
	}
	pipe_node = ast_node_create(ctx->arena, NODE_PIPE);
	if (!pipe_node)
		return (NULL);
	pipe_node->left = left;
	right = parse_job(ctx);
	if (!right)
		return (NULL);
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*parse_job(t_parse_ctx *ctx)
{
	t_ast_node	*left;

	left = parse_simple_command(ctx);
	if (!left)
		return (NULL);
	if (parser_match(ctx, TOKEN_PIPE))
		return (parse_pipe_sequence(ctx, left));
	return (left);
}
