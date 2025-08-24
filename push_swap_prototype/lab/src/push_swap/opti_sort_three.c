/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_sort_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:16 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 21:58:02 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	sort_three(t_ps *data, t_chunk *to_sort)
{
	t_stack	*stk;
	int		max;

	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	stk = loc_to_stack(data, to_sort->loc);
	DEBUG_VAR(data, "stk", "loc_to_stack(data, to_sort->loc)");
	DEBUG_LINE(data, __LINE__);
	
	max = chunk_max_value(data, to_sort);
	DEBUG_VAR(data, "max", "chunk_max_value(data, to_sort)");
	DEBUG_LINE(data, __LINE__);
	
	if (to_sort->loc == TOP_A)
	{
		DEBUG_VAR(data, "condition", "to_sort->loc == TOP_A");
		DEBUG_LINE(data, __LINE__);
		sort_three_top_a(data, to_sort, stk, max);
		DEBUG_AFTER_OP(data, "sort_three_top_a");
	}
	else if (to_sort->loc == BOTTOM_A)
	{
		DEBUG_VAR(data, "condition", "to_sort->loc == BOTTOM_A");
		DEBUG_LINE(data, __LINE__);
		sort_three_bottom_a(data, to_sort, stk, max);
		DEBUG_AFTER_OP(data, "sort_three_bottom_a");
	}
	else if (to_sort->loc == TOP_B)
	{
		DEBUG_VAR(data, "condition", "to_sort->loc == TOP_B");
		DEBUG_LINE(data, __LINE__);
		sort_three_top_b(data, to_sort, stk, max);
		DEBUG_AFTER_OP(data, "sort_three_top_b");
	}
	else if (to_sort->loc == BOTTOM_B)
	{
		DEBUG_VAR(data, "condition", "to_sort->loc == BOTTOM_B");
		DEBUG_LINE(data, __LINE__);
		sort_three_bottom_b(data, to_sort, stk, max);
		DEBUG_AFTER_OP(data, "sort_three_bottom_b");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	sort_three_top_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "max", "max");
	
	if (stk->stack[stk->top] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[stk->top] == max");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
		DEBUG_LINE(data, __LINE__);
		rotate_a(data);
		DEBUG_AFTER_OP(data, "rotate_a");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a (second)");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a");
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[next_down(stk, stk->top)] == max");
		DEBUG_LINE(data, __LINE__);
		rotate_a(data);
		DEBUG_AFTER_OP(data, "rotate_a");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a");
	}
	to_sort->loc = TOP_A;
	DEBUG_VAR(data, "to_sort->loc", "TOP_A");
	DEBUG_LINE(data, __LINE__);
	
	to_sort->size -= 1;
	DEBUG_VAR(data, "to_sort->size", "decremented");
	DEBUG_LINE(data, __LINE__);
	
	sort_two(data, to_sort);
	DEBUG_AFTER_OP(data, "sort_two");
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	sort_three_top_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "max", "max");
	
	push_a(data);
	DEBUG_AFTER_OP(data, "push_a (first)");
	DEBUG_LINE(data, __LINE__);
	
	if (stk->stack[stk->top] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[stk->top] == max");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a (second)");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[next_down(stk, stk->top)] == max");
		DEBUG_LINE(data, __LINE__);
		swap_b(data);
		DEBUG_AFTER_OP(data, "swap_b");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a (second)");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
	}
	else
	{
		DEBUG_VAR(data, "condition", "else");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a (second)");
	}
	DEBUG_LINE(data, __LINE__);
	
	push_a(data);
	DEBUG_AFTER_OP(data, "push_a (third)");
	DEBUG_LINE(data, __LINE__);
	
	to_sort->loc = TOP_A;
	DEBUG_VAR(data, "to_sort->loc", "TOP_A");
	DEBUG_LINE(data, __LINE__);
	
	to_sort->size -= 1;
	DEBUG_VAR(data, "to_sort->size", "decremented");
	DEBUG_LINE(data, __LINE__);
	
	sort_two(data, to_sort);
	DEBUG_AFTER_OP(data, "sort_two");
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	sort_three_bottom_a(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "max", "max");
	
	r_rotate_a(data);
	DEBUG_AFTER_OP(data, "r_rotate_a (first)");
	DEBUG_LINE(data, __LINE__);
	
	r_rotate_a(data);
	DEBUG_AFTER_OP(data, "r_rotate_a (second)");
	DEBUG_LINE(data, __LINE__);
	
	if (stk->stack[stk->top] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[stk->top] == max");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a (third)");
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[next_down(stk, stk->top)] == max");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a (third)");
	}
	else
	{
		DEBUG_VAR(data, "condition", "else");
		DEBUG_LINE(data, __LINE__);
		push_b(data);
		DEBUG_AFTER_OP(data, "push_b");
		DEBUG_LINE(data, __LINE__);
		r_rotate_a(data);
		DEBUG_AFTER_OP(data, "r_rotate_a (third)");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
	}
	DEBUG_LINE(data, __LINE__);
	
	to_sort->loc = TOP_A;
	DEBUG_VAR(data, "to_sort->loc", "to_sort->loc = TOP_A");
	DEBUG_LINE(data, __LINE__);
	
	to_sort->size -= 1;
	DEBUG_VAR(data, "to_sort->size", "decremented");
	DEBUG_LINE(data, __LINE__);
	
	sort_two(data, to_sort);
	DEBUG_AFTER_OP(data, "sort_two");
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	sort_three_bottom_b(t_ps *data, t_chunk *to_sort, t_stack *stk, int max)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	DEBUG_VAR(data, "max", "max");
	
	r_rotate_b(data);
	DEBUG_AFTER_OP(data, "r_rotate_b (first)");
	DEBUG_LINE(data, __LINE__);
	
	r_rotate_b(data);
	DEBUG_AFTER_OP(data, "r_rotate_b (second)");
	DEBUG_LINE(data, __LINE__);
	
	if (stk->stack[stk->top] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[stk->top] == max");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
		DEBUG_LINE(data, __LINE__);
		r_rotate_b(data);
		DEBUG_AFTER_OP(data, "r_rotate_b (third)");
	}
	else if (stk->stack[next_down(stk, stk->top)] == max)
	{
		DEBUG_VAR(data, "condition", "stk->stack[next_down(stk, stk->top)] == max");
		DEBUG_LINE(data, __LINE__);
		swap_b(data);
		DEBUG_AFTER_OP(data, "swap_b");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
		DEBUG_LINE(data, __LINE__);
		r_rotate_b(data);
		DEBUG_AFTER_OP(data, "r_rotate_b (third)");
	}
	else
	{
		DEBUG_VAR(data, "condition", "else");
		DEBUG_LINE(data, __LINE__);
		r_rotate_b(data);
		DEBUG_AFTER_OP(data, "r_rotate_b (third)");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a");
	}
	DEBUG_LINE(data, __LINE__);
	
	to_sort->loc = TOP_B;
	DEBUG_VAR(data, "to_sort->loc", "TOP_B");
	DEBUG_LINE(data, __LINE__);
	
	to_sort->size -= 1;
	DEBUG_VAR(data, "to_sort->size", "decremented");
	DEBUG_LINE(data, __LINE__);
	
	sort_two(data, to_sort);
	DEBUG_AFTER_OP(data, "sort_two");
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}