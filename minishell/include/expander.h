/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:31:56 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:59:31 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "state.h"

typedef struct s_exp_ctx
{
	t_arena		*arena;
	t_env		*env_list;
	int			exit_code;
	t_str8_list	builder;
	t_str8_list	expanded_words;
	bool		in_sq;
	bool		in_dq;
	bool		was_quoted;
}				t_exp_ctx;

void			expand_ast(t_shell *shell, t_ast_node *node);
t_str8_list		expand_word(t_exp_ctx *ctx, t_str8 word);

void			exp_builder_append(t_arena *arena, t_str8_list *list,
					t_str8 str);
t_str8			exp_builder_flatten(t_arena *arena, t_str8_list *list);

t_str8			exp_get_var_val(t_exp_ctx *ctx, t_str8 key);
t_str8			exp_handle_tilde(t_exp_ctx *ctx, t_str8 word);
void			flush_segment(t_exp_ctx *ctx, char *anchor, char *cursor);
void			exp_ctx_reset_for_word(t_exp_ctx *ctx);
void			expand_node_redirs(t_exp_ctx *ctx, t_token *redir);
char			*find_var_end(char *start);
void			flush_current_word(t_exp_ctx *ctx);
void			process_dollar_split(t_exp_ctx *ctx, t_str8 val);
void			expand_non_heredoc_tokens(t_exp_ctx *ctx, t_token *redir);

#endif
