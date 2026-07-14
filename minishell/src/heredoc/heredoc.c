/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:56 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:29:47 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/heredoc.h"

static bool	process_single_redir(t_hdoc_ctx *ctx, t_token *tok, int *id)
{
	t_str8	delim;
	t_str8	tmp;
	bool	expand;
	char	*tmp_cstr;

	delim = heredoc_strip_quotes(ctx->arena, tok->value, &expand);
	tmp = heredoc_generate_name(ctx->arena, (*id)++);
	tmp_cstr = str8_to_cstr(ctx->arena, tmp);
	if (delim.str && tmp_cstr)
	{
		if (!heredoc_process_file(ctx, tmp_cstr, delim, expand))
			return (false);
		tok->type = TOKEN_REDIRECT_HEREDOC;
		tok->value = tmp;
	}
	return (true);
}

static bool	handle_cmd_heredocs(t_hdoc_ctx *ctx, t_ast_node *node, int *id)
{
	t_token	*tok;

	tok = node->redirs;
	while (tok)
	{
		if (tok->type == TOKEN_REDIRECT_HEREDOC)
		{
			if (!process_single_redir(ctx, tok, id))
				return (false);
		}
		tok = tok->next;
	}
	return (true);
}

static bool	traverse_ast(t_hdoc_ctx *ctx, t_ast_node *node, int *id)
{
	if (!node)
		return (true);
	if (node->type == NODE_PIPE)
	{
		if (!traverse_ast(ctx, node->left, id))
			return (false);
		return (traverse_ast(ctx, node->right, id));
	}
	return (handle_cmd_heredocs(ctx, node, id));
}

bool	process_heredocs(t_hdoc_ctx *ctx, t_ast_node *root)
{
	int	id;

	id = 0;
	return (traverse_ast(ctx, root, &id));
}
