/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:36:29 by omaly             #+#    #+#             */
/*   Updated: 2026/03/04 16:59:13 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	expand_non_heredoc_tokens(t_exp_ctx *ctx, t_token *redir)
{
	t_str8_list	split;

	if (redir->type == TOKEN_REDIRECT_HEREDOC)
		return ;
	exp_ctx_reset_for_word(ctx);
	redir->value = exp_handle_tilde(ctx, redir->value);
	split = expand_word(ctx, redir->value);
	if (!split.first || split.first->next != NULL)
	{
		shell_error("minishell", (char *)redir->value.str,
			"ambiguous redirect");
		redir->value = (t_str8){NULL, 0};
		return ;
	}
	redir->value = split.first->string;
}

static int	count_args(t_str8_list *list)
{
	int			count;
	t_str8_node	*curr;

	count = 0;
	curr = list->first;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

static void	rebuild_args_array(t_exp_ctx *ctx, t_ast_node *node,
		t_str8_list *list)
{
	int			i;
	t_str8_node	*curr;

	i = count_args(list);
	node->args = ft_arena_push(ctx->arena, sizeof(t_str8) * (i + 1));
	if (!node->args)
		return ;
	curr = list->first;
	i = 0;
	while (curr)
	{
		node->args[i++] = curr->string;
		curr = curr->next;
	}
	node->args[i] = (t_str8){NULL, 0};
}

static void	expand_cmd_node(t_exp_ctx *ctx, t_ast_node *node)
{
	int			i;
	t_str8_list	new_args;
	t_str8_list	split;
	t_str8_node	*curr;

	new_args = (t_str8_list){0};
	i = -1;
	while (node->args && node->args[++i].str != NULL)
	{
		exp_ctx_reset_for_word(ctx);
		split = expand_word(ctx, exp_handle_tilde(ctx, node->args[i]));
		curr = split.first;
		while (curr)
		{
			exp_builder_append(ctx->arena, &new_args, curr->string);
			curr = curr->next;
		}
	}
	rebuild_args_array(ctx, node, &new_args);
	expand_node_redirs(ctx, node->redirs);
}

void	expand_ast(t_shell *shell, t_ast_node *node)
{
	t_exp_ctx	ctx;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		expand_ast(shell, node->left);
		expand_ast(shell, node->right);
		return ;
	}
	ctx.arena = shell->cmd_arena;
	ctx.env_list = shell->env_list;
	ctx.exit_code = shell->exit_code;
	expand_cmd_node(&ctx, node);
}
