/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:50:05 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 23:11:53 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static bool	is_inverse(t_operation a, t_operation b)
{
	if (a == RA)
		return (b == RRA);
	if (a == RRA)
		return (b == RA);
	if (a == RB)
		return (b == RRB);
	if (a == RRB)
		return (b == RB);
	if (a == RR)
		return (b == RRR);
	if (a == RRR)
		return (b == RR);
	if (a == SA)
		return (b == SA);
	if (a == SB)
		return (b == SB);
	if (a == SS)
		return (b == SS);
	if (a == PA)
		return (b == PB);
	if (a == PB)
		return (b == PA);
	return (false);
}

static void	process_inverse_cancellation(t_list *src, t_list **dst,
		bool *has_changed)
{
	t_list	*current;

	current = src;
	while (current != NULL)
	{
		if (current->next != NULL
			&& is_inverse(*(t_operation *)current->content,
				*(t_operation *)current->next->content))
		{
			*has_changed = true;
			current = current->next->next;
		}
		else
		{
			add_operation_to_list(dst, *(t_operation *)current->content);
			current = current->next;
		}
	}
}

t_list	*cancel_inverse_pairs(t_list *src, bool *changed)
{
	t_list				*dst;
	bool				has_changed;

	if (!src || ft_lstsize(src) < 2)
	{
		if (changed)
			*changed = false;
		return (ft_lstmap(src, copy_operation, free));
	}
	dst = NULL;
	has_changed = false;
	process_inverse_cancellation(src, &dst, &has_changed);
	if (changed)
		*changed = has_changed;
	return (dst);
}
