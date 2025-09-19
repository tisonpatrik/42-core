/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:30 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 20:49:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

bool	try_merge_rotate_pairs(t_operation a, t_operation b, t_list **dst,
		t_list **current)
{
	if ((a == RA && b == RB) || (a == RB && b == RA))
	{
		add_operation_to_list(dst, RR);
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRA && b == RRB) || (a == RRB && b == RRA))
	{
		add_operation_to_list(dst, RRR);
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}

bool	try_merge_swap_pairs(t_operation a, t_operation b, t_list **dst,
		t_list **current)
{
	if ((a == SA && b == SB) || (a == SB && b == SA))
	{
		add_operation_to_list(dst, SS);
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}

bool	try_merge_absorption_cases(t_operation a, t_operation b, t_list **dst,
		t_list **current)
{
	if ((a == RR && b == RRA) || (a == RRA && b == RR))
	{
		add_operation_to_list(dst, get_absorption_result_rr_rra(a));
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RR && b == RRB) || (a == RRB && b == RR))
	{
		add_operation_to_list(dst, get_absorption_result_rr_rrb(a));
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRR && b == RA) || (a == RA && b == RRR))
	{
		add_operation_to_list(dst, get_absorption_result_rrr_ra(a));
		*current = (*current)->next->next;
		return (true);
	}
	if ((a == RRR && b == RB) || (a == RB && b == RRR))
	{
		add_operation_to_list(dst, get_absorption_result_rrr_rb(a));
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}
