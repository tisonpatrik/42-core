/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:07:22 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:28:50 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/heredoc.h"

void	write_exit_code(t_hdoc_ctx *ctx)
{
	char	*code_str;

	code_str = ft_itoa(ctx->last_exit_code);
	if (!code_str)
		return ;
	hdoc_write(ctx->fd, ft_str8_from_cstr(code_str));
	free(code_str);
}

void	heredoc_cleanup(t_ast_node *node)
{
	t_token	*tok;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		heredoc_cleanup(node->left);
		heredoc_cleanup(node->right);
		return ;
	}
	tok = node->redirs;
	while (tok)
	{
		if (tok->type == TOKEN_REDIRECT_HEREDOC && tok->value.str)
			unlink((char *)tok->value.str);
		tok = tok->next;
	}
}
