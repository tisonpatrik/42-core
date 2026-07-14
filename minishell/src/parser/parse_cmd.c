/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:38:04 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:28:34 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	append_arg(t_arena *arena, t_str8_list *list, t_str8 val)
{
	t_str8_node	*node;

	node = ft_arena_push(arena, sizeof(t_str8_node));
	if (!node)
		return ;
	node->string = val;
	node->next = NULL;
	if (!list->first)
		list->first = node;
	else
		list->last->next = node;
	list->last = node;
	list->total_size++;
}

static void	build_args_array(t_parse_ctx *ctx, t_ast_node *node,
		t_str8_list *list)
{
	int			i;
	t_str8_node	*curr;

	if (!ast_node_init_args(ctx->arena, node, list->total_size))
	{
		ctx->error = true;
		return ;
	}
	i = 0;
	curr = list->first;
	while (curr)
	{
		node->args[i++] = curr->string;
		curr = curr->next;
	}
}

static t_ast_node	*prepare_cmd_node(t_parse_ctx *ctx)
{
	t_ast_node	*node;

	if (parser_peek(ctx) == TOKEN_PIPE || parser_peek(ctx) == TOKEN_EOF)
		return (NULL);
	node = ast_node_create(ctx->arena, NODE_COMMAND);
	return (node);
}

t_ast_node	*parse_simple_command(t_parse_ctx *ctx)
{
	t_ast_node	*node;
	t_str8_list	arg_list;
	t_token		*tok;

	node = prepare_cmd_node(ctx);
	if (!node)
		return (NULL);
	arg_list = (t_str8_list){0};
	while (!ctx->error && parser_peek(ctx) != TOKEN_PIPE
		&& parser_peek(ctx) != TOKEN_EOF)
	{
		if (is_redir_token(parser_peek(ctx)))
			parse_redir(ctx, node);
		else
		{
			tok = parser_eat(ctx);
			append_arg(ctx->arena, &arg_list, tok->value);
		}
	}
	if (ctx->error)
		return (NULL);
	build_args_array(ctx, node, &arg_list);
	return (node);
}
