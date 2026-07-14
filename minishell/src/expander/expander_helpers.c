/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:52:29 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:35:06 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	flush_segment(t_exp_ctx *ctx, char *anchor, char *cursor)
{
	if (cursor > anchor)
		exp_builder_append(ctx->arena, &ctx->builder,
			ft_str8_create((uint8_t *)anchor, cursor - anchor));
}

void	exp_ctx_reset_for_word(t_exp_ctx *ctx)
{
	ctx->builder = (t_str8_list){0};
	ctx->expanded_words = (t_str8_list){0};
	ctx->in_sq = false;
	ctx->in_dq = false;
	ctx->was_quoted = false;
}

void	expand_node_redirs(t_exp_ctx *ctx, t_token *redir)
{
	while (redir)
	{
		expand_non_heredoc_tokens(ctx, redir);
		redir = redir->next;
	}
}
