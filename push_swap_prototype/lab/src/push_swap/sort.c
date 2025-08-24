/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:28 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 18:59:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	sort(t_ps *data)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	if (data->a.size <= 1 || is_sorted(data))
	{
		DEBUG_VAR(data, "condition", "data->a.size <= 1 || is_sorted(data)");
		DEBUG_LINE(data, __LINE__);
		DEBUG_FUNC_EXIT(data);
		return ;
	}
	else if (data->a.size == 3)
	{
		DEBUG_VAR(data, "data->a.size", "== 3");
		DEBUG_LINE(data, __LINE__);
		sort_three_a(data);
		DEBUG_AFTER_OP(data, "sort_three_a");
	}
	else if (data->a.size == 5)
	{
		DEBUG_VAR(data, "data->a.size", "== 5");
		DEBUG_LINE(data, __LINE__);
		sort_five_a(data);
		DEBUG_AFTER_OP(data, "sort_five_a");
	}
	else
	{
		DEBUG_VAR(data, "data->a.size", "> 5, using chunk_sort");
		DEBUG_LINE(data, __LINE__);
		chunk_sort(data);
		DEBUG_AFTER_OP(data, "chunk_sort");
	}
	
	DEBUG_LINE(data, __LINE__);
	post_sort_optimization(data);
	DEBUG_AFTER_OP(data, "post_sort_optimization");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_FUNC_EXIT(data);
}

void	sort_three_a(t_ps *data)
{
	int	first;
	int	second;
	int	third;

	first = value(&data->a, 1);
	second = value(&data->a, 2);
	third = value(&data->a, 3);
	if (first > second && third > second && third > first)
		swap_a(data);
	else if (first > second && third > second && first > third)
		rotate_a(data);
	else if (second > first && second > third && first > third)
		r_rotate_a(data);
	else if (second > first && second > third && third > first)
	{
		swap_a(data);
		rotate_a(data);
	}
	else if (first > second && second > third && first > third)
	{
		swap_a(data);
		r_rotate_a(data);
	}
}

void	sort_five_a(t_ps *data)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	while (current_size(&data->a) > 3)
	{
		DEBUG_VAR(data, "current_size(&data->a)", "> 3");
		DEBUG_LINE(data, __LINE__);
		
		if (value(&data->a, 1) == 1 || value(&data->a, 1) == 2)
		{
			DEBUG_VAR(data, "value(&data->a, 1)", "== 1 || == 2");
			DEBUG_LINE(data, __LINE__);
			DEBUG_BEFORE_OP(data, "push_b");
			push_b(data);
			DEBUG_AFTER_OP(data, "push_b");
		}
		else
		{
			DEBUG_VAR(data, "value(&data->a, 1)", "!= 1 && != 2");
			DEBUG_LINE(data, __LINE__);
			DEBUG_BEFORE_OP(data, "rotate_a");
			rotate_a(data);
			DEBUG_AFTER_OP(data, "rotate_a");
		}
		DEBUG_LINE(data, __LINE__);
	}
	
	DEBUG_VAR(data, "current_size(&data->a)", "<= 3");
	DEBUG_LINE(data, __LINE__);
	
	if (value(&data->b, 1) < value(&data->b, 2))
	{
		DEBUG_VAR(data, "value(&data->b, 1) < value(&data->b, 2)", "true");
		DEBUG_LINE(data, __LINE__);
		DEBUG_BEFORE_OP(data, "swap_b");
		swap_b(data);
		DEBUG_AFTER_OP(data, "swap_b");
	}
	
	DEBUG_LINE(data, __LINE__);
	DEBUG_BEFORE_OP(data, "sort_three_a");
	sort_three_a(data);
	DEBUG_AFTER_OP(data, "sort_three_a");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_BEFORE_OP(data, "push_a 1");
	push_a(data);
	DEBUG_AFTER_OP(data, "push_a 1");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_BEFORE_OP(data, "push_a 2");
	push_a(data);
	DEBUG_AFTER_OP(data, "push_a 2");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_FUNC_EXIT(data);
}
