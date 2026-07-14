/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:37:44 by omaly             #+#    #+#             */
/*   Updated: 2026/02/26 12:37:49 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

t_token	*token_create(t_arena *arena, t_str8 value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)ft_arena_push(arena, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **list, t_token *new_tok)
{
	t_token	*tmp;

	if (!list || !new_tok)
		return ;
	if (!*list)
	{
		*list = new_tok;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_tok;
}
