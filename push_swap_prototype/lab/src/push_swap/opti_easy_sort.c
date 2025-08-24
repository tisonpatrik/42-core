/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_easy_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:15 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 21:51:01 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	easy_sort(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	while (to_sort->loc != TOP_A && to_sort->size)
	{
		DEBUG_LINE(data, __LINE__);
		if (value(&data->a, 1) == chunk_value(data, to_sort, 1) + 1
			&& to_sort->size > 0)
		{
			DEBUG_VAR(data, "condition", "value(&data->a, 1) == chunk_value(data, to_sort, 1) + 1");
			DEBUG_LINE(data, __LINE__);
			sort_one(data, to_sort);
			DEBUG_AFTER_OP(data, "sort_one");
		}
		else if (value(&data->a, 1) == chunk_value(data, to_sort, 2) + 1
			&& to_sort->size > 1)
		{
			DEBUG_VAR(data, "condition", "value(&data->a, 1) == chunk_value(data, to_sort, 2) + 1");
			DEBUG_LINE(data, __LINE__);
			easy_sort_second(data, to_sort);
			DEBUG_AFTER_OP(data, "easy_sort_second");
		}
		else
		{
			DEBUG_VAR(data, "condition", "else - breaking loop");
			DEBUG_LINE(data, __LINE__);
			break ;
		}
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	easy_sort_second(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	if (to_sort->loc == TOP_B)
	{
		DEBUG_VAR(data, "to_sort->loc", "TOP_B");
		DEBUG_LINE(data, __LINE__);
		handle_top_b(data, to_sort);
		DEBUG_AFTER_OP(data, "handle_top_b");
	}
	else if (to_sort->loc == BOTTOM_A)
	{
		DEBUG_VAR(data, "to_sort->loc", "BOTTOM_A");
		DEBUG_LINE(data, __LINE__);
		handle_bottom_a(data, to_sort);
		DEBUG_AFTER_OP(data, "handle_bottom_a");
	}
	else if (to_sort->loc == BOTTOM_B)
	{
		DEBUG_VAR(data, "to_sort->loc", "BOTTOM_B");
		DEBUG_LINE(data, __LINE__);
		handle_bottom_b(data, to_sort);
		DEBUG_AFTER_OP(data, "handle_bottom_b");
	}
	to_sort->size--;
	DEBUG_VAR(data, "to_sort->size", "decremented");
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	handle_top_b(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	swap_b(data);
	DEBUG_AFTER_OP(data, "swap_b");
	DEBUG_LINE(data, __LINE__);
	
	push_a(data);
	DEBUG_AFTER_OP(data, "push_a");
	DEBUG_LINE(data, __LINE__);
	
	if (value(&data->b, 1) == value(&data->a, 1) - 1)
	{
		DEBUG_VAR(data, "condition", "value(&data->b, 1) == value(&data->a, 1) - 1");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a (second)");
		to_sort->size--;
		DEBUG_VAR(data, "to_sort->size", "decremented");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	handle_bottom_a(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	r_rotate_a(data);
	DEBUG_AFTER_OP(data, "r_rotate_a (first)");
	DEBUG_LINE(data, __LINE__);
	
	r_rotate_a(data);
	DEBUG_AFTER_OP(data, "r_rotate_a (second)");
	DEBUG_LINE(data, __LINE__);
	
	swap_a(data);
	DEBUG_AFTER_OP(data, "swap_a");
	DEBUG_LINE(data, __LINE__);
	
	if (value(&data->a, 1) == value(&data->a, 2) - 1)
	{
		DEBUG_VAR(data, "condition", "value(&data->a, 1) == value(&data->a, 2) - 1");
		DEBUG_LINE(data, __LINE__);
		to_sort->size--;
		DEBUG_VAR(data, "to_sort->size", "decremented");
	}
	else
	{
		DEBUG_VAR(data, "condition", "else - rotating a");
		DEBUG_LINE(data, __LINE__);
		rotate_a(data);
		DEBUG_AFTER_OP(data, "rotate_a");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}

void	handle_bottom_b(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	r_rotate_b(data);
	DEBUG_AFTER_OP(data, "r_rotate_b (first)");
	DEBUG_LINE(data, __LINE__);
	
	r_rotate_b(data);
	DEBUG_AFTER_OP(data, "r_rotate_b (second)");
	DEBUG_LINE(data, __LINE__);
	
	push_a(data);
	DEBUG_AFTER_OP(data, "push_a");
	DEBUG_LINE(data, __LINE__);
	
	if (value(&data->b, 1) == value(&data->a, 1) - 1)
	{
		DEBUG_VAR(data, "condition", "value(&data->b, 1) == value(&data->a, 1) - 1");
		DEBUG_LINE(data, __LINE__);
		push_a(data);
		DEBUG_AFTER_OP(data, "push_a (second)");
		to_sort->size--;
		DEBUG_VAR(data, "to_sort->size", "decremented");
	}
	else
	{
		DEBUG_VAR(data, "condition", "else - rotating b");
		DEBUG_LINE(data, __LINE__);
		rotate_b(data);
		DEBUG_AFTER_OP(data, "rotate_b");
	}
	DEBUG_LINE(data, __LINE__);
	DEBUG_FUNC_EXIT(data);
}
