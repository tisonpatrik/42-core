/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:32:14 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:32:17 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/include/libft.h"
# include "error.h"
# include "lexer.h"
# include "types.h"

typedef struct s_parse_ctx
{
	t_token				*curr;
	t_arena				*arena;
	bool				error;
}						t_parse_ctx;

typedef struct s_ast_node
{
	t_node_type			type;
	t_str8				*args;
	t_token				*redirs;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				*path;
}						t_ast_node;

void					parser_init(t_parse_ctx *ctx, t_arena *arena,
							t_token *tokens);
t_token_type			parser_peek(t_parse_ctx *ctx);
t_ast_node				*parse_job(t_parse_ctx *ctx);
t_ast_node				*parse_simple_command(t_parse_ctx *ctx);
t_token					*parser_eat(t_parse_ctx *ctx);
bool					parser_match(t_parse_ctx *ctx, t_token_type type);
bool					is_redir_token(t_token_type type);
bool					parser_match(t_parse_ctx *ctx, t_token_type type);
t_ast_node				*ast_node_create(t_arena *arena, t_node_type type);
bool					ast_node_init_args(t_arena *arena, t_ast_node *node,
							int count);
bool					parse_redir(t_parse_ctx *ctx, t_ast_node *node);
t_ast_node				*parser_build_ast(t_arena *arena, t_token *tokens);
#endif
