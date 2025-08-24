/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:08 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 21:52:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

int	move_from_to(t_ps *data, t_loc from, t_loc to)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "from", from == TOP_A ? "TOP_A" : from == TOP_B ? "TOP_B" : from == BOTTOM_A ? "BOTTOM_A" : "BOTTOM_B");
	DEBUG_VAR(data, "to", to == TOP_A ? "TOP_A" : to == TOP_B ? "TOP_B" : to == BOTTOM_A ? "BOTTOM_A" : "BOTTOM_B");
	
	if (from == TOP_A)
	{
		DEBUG_VAR(data, "condition", "from == TOP_A");
		DEBUG_LINE(data, __LINE__);
		move_from_top_a(data, to);
		DEBUG_AFTER_OP(data, "move_from_top_a");
	}
	else if (from == TOP_B)
	{
		DEBUG_VAR(data, "condition", "from == TOP_B");
		DEBUG_LINE(data, __LINE__);
		move_from_top_b(data, to);
		DEBUG_AFTER_OP(data, "move_from_top_b");
	}
	else if (from == BOTTOM_A)
	{
		DEBUG_VAR(data, "condition", "from == BOTTOM_A");
		DEBUG_LINE(data, __LINE__);
		move_from_bottom_a(data, to);
		DEBUG_AFTER_OP(data, "move_from_bottom_a");
	}
	else if (from == BOTTOM_B)
	{
		DEBUG_VAR(data, "condition", "from == BOTTOM_B");
		DEBUG_LINE(data, __LINE__);
		move_from_bottom_b(data, to);
		DEBUG_AFTER_OP(data, "move_from_bottom_b");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
	return (1);
}

void	move_from_top_a(t_ps *data, t_loc to)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "to", to == TOP_B ? "TOP_B" : to == BOTTOM_A ? "BOTTOM_A" : "BOTTOM_B");
	
	if (to == TOP_B)
	{
		DEBUG_VAR(data, "condition", "to == TOP_B");
		DEBUG_LINE(data, __LINE__);
		push_b(data);
		DEBUG_AFTER_OP(data, "push_b");
	}
	else if (to == BOTTOM_A)
	{
		DEBUG_VAR(data, "condition", "to == BOTTOM_A");
		DEBUG_LINE(data, __LINE__);
		rotate_a(data);
		DEBUG_AFTER_OP(data, "rotate_a");
	}
	else if (to == BOTTOM_B)
	{
		DEBUG_VAR(data, "condition", "to == BOTTOM_B");
		DEBUG_LINE(data, __LINE__);
		push_b(data);
		DEBUG_AFTER_OP(data, "push_b (first)");
		DEBUG_LINE(data, __LINE__);
		rotate_b(data);
		DEBUG_AFTER_OP(data, "rotate_b");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	move_from_top_b(t_ps *data, t_loc to)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "to", to == TOP_A ? "TOP_A" : to == BOTTOM_B ? "BOTTOM_B" : "BOTTOM_A");
	
	if (to == TOP_A)
	{
		DEBUG_VAR(data, "condition", "to == TOP_A");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
	}
	else if (to == BOTTOM_B)
	{
		DEBUG_VAR(data, "condition", "to == BOTTOM_B");
		DEBUG_LINE(data, __LINE__);
		rotate_b(data);
		DEBUG_AFTER_OP(data, "rotate_b");
	}
	else if (to == BOTTOM_A)
	{
		DEBUG_VAR(data, "condition", "to == BOTTOM_A");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a (first)");
		DEBUG_LINE(data, __LINE__);
		rotate_a(data);
		DEBUG_AFTER_OP(data, "rotate_a");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	move_from_bottom_a(t_ps *data, t_loc to)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "to", to == TOP_A ? "TOP_A" : to == TOP_B ? "TOP_B" : "BOTTOM_B");
	
	if (to == TOP_A)
	{
		DEBUG_VAR(data, "condition", "to == TOP_A");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a");
	}
	else if (to == TOP_B)
	{
		DEBUG_VAR(data, "condition", "to == TOP_B");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a (first)");
		DEBUG_LINE(data, __LINE__);
		push_b(data);
		DEBUG_AFTER_OP(data, "push_b");
	}
	else if (to == BOTTOM_B)
	{
		DEBUG_VAR(data, "condition", "to == BOTTOM_B");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a (first)");
		DEBUG_LINE(data, __LINE__);
		push_b(data);
		DEBUG_AFTER_OP(data, "push_b");
		DEBUG_LINE(data, __LINE__);
		rotate_b(data);
		DEBUG_AFTER_OP(data, "rotate_b");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	move_from_bottom_b(t_ps *data, t_loc to)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "to", to == TOP_B ? "TOP_B" : to == TOP_A ? "TOP_A" : "BOTTOM_A");
	
	if (to == TOP_B)
	{
		DEBUG_VAR(data, "condition", "to == TOP_B");
		DEBUG_LINE(data, __LINE__);
		r_rotate_b(data);
		DEBUG_AFTER_OP(data, "r_rotate_b");
	}
	else if (to == TOP_A)
	{
		DEBUG_VAR(data, "condition", "to == TOP_A");
		DEBUG_LINE(data, __LINE__);
		r_rotate_b(data);
		DEBUG_AFTER_OP(data, "r_rotate_b (first)");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
	}
	else if (to == BOTTOM_A)
	{
		DEBUG_VAR(data, "condition", "to == BOTTOM_A");
		DEBUG_LINE(data, __LINE__);
		r_rotate_b(data);
		DEBUG_AFTER_OP(data, "r_rotate_b (first)");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
		DEBUG_LINE(data, __LINE__);
		rotate_a(data);
		DEBUG_AFTER_OP(data, "rotate_a");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}
