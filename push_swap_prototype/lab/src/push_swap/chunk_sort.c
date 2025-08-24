/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:55 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 18:57:59 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	chunk_sort(t_ps *data)
{
	t_chunk	chunk_all;

	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	chunk_all.loc = TOP_A;
	DEBUG_VAR(data, "chunk_all.loc", "TOP_A");
	DEBUG_LINE(data, __LINE__);
	
	chunk_all.size = data->a.size;
	DEBUG_VAR(data, "chunk_all.size", "data->a.size");
	DEBUG_LINE(data, __LINE__);
	
	rec_chunk_sort(data, &chunk_all);
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_FUNC_EXIT(data);
}

void	rec_chunk_sort(t_ps *data, t_chunk *to_sort)
{
	t_split_dest	dest;

	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	chunk_to_the_top(data, to_sort);
	DEBUG_AFTER_OP(data, "chunk_to_the_top");
	DEBUG_LINE(data, __LINE__);
	
	easy_sort(data, to_sort);
	DEBUG_AFTER_OP(data, "easy_sort");
	DEBUG_LINE(data, __LINE__);
	
	if (to_sort->size <= 3)
	{
		DEBUG_VAR(data, "to_sort->size", "<= 3");
		DEBUG_LINE(data, __LINE__);
		
		if (to_sort->size == 3)
		{
			DEBUG_VAR(data, "to_sort->size", "== 3");
			DEBUG_LINE(data, __LINE__);
			sort_three(data, to_sort);
			DEBUG_AFTER_OP(data, "sort_three");
		}
		else if (to_sort->size == 2)
		{
			DEBUG_VAR(data, "to_sort->size", "== 2");
			DEBUG_LINE(data, __LINE__);
			sort_two(data, to_sort);
			DEBUG_AFTER_OP(data, "sort_two");
		}
		else if (to_sort->size == 1)
		{
			DEBUG_VAR(data, "to_sort->size", "== 1");
			DEBUG_LINE(data, __LINE__);
			sort_one(data, to_sort);
			DEBUG_AFTER_OP(data, "sort_one");
		}
		DEBUG_LINE(data, __LINE__);
		return ;
	}
	
	DEBUG_VAR(data, "to_sort->size", "> 3");
	DEBUG_LINE(data, __LINE__);
	
	chunk_split(data, to_sort, &dest);
	DEBUG_AFTER_OP(data, "chunk_split");
	DEBUG_LINE(data, __LINE__);
	
	rec_chunk_sort(data, &dest.max);
	DEBUG_AFTER_OP(data, "rec_chunk_sort dest.max");
	DEBUG_LINE(data, __LINE__);
	
	rec_chunk_sort(data, &dest.mid);
	DEBUG_AFTER_OP(data, "rec_chunk_sort dest.mid");
	DEBUG_LINE(data, __LINE__);
	
	rec_chunk_sort(data, &dest.min);
	DEBUG_AFTER_OP(data, "rec_chunk_sort dest.min");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_FUNC_EXIT(data);
}

void	sort_two(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		DEBUG_VAR(data, "to_sort->loc", "BOTTOM_A || BOTTOM_B || TOP_B");
		DEBUG_LINE(data, __LINE__);
		
		move_from_to(data, to_sort->loc, TOP_A);
		DEBUG_AFTER_OP(data, "move_from_to 1");
		DEBUG_LINE(data, __LINE__);
		
		move_from_to(data, to_sort->loc, TOP_A);
		DEBUG_AFTER_OP(data, "move_from_to 2");
		DEBUG_LINE(data, __LINE__);
	}
	
	if (value(&data->a, 1) > value(&data->a, 2))
	{
		DEBUG_VAR(data, "value comparison", "value(&data->a, 1) > value(&data->a, 2)");
		DEBUG_LINE(data, __LINE__);
		swap_a(data);
		DEBUG_AFTER_OP(data, "swap_a");
	}
	
	to_sort->size -= 2;
	DEBUG_VAR(data, "to_sort->size", "decreased by 2");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_FUNC_EXIT(data);
}

void	sort_one(t_ps *data, t_chunk *to_sort)
{
	DEBUG_FUNC_ENTRY(data);
	DEBUG_LINE(data, __LINE__);
	
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		DEBUG_VAR(data, "to_sort->loc", "BOTTOM_A || BOTTOM_B || TOP_B");
		DEBUG_LINE(data, __LINE__);
		move_from_to(data, to_sort->loc, TOP_A);
		DEBUG_AFTER_OP(data, "move_from_to");
	}
	
	to_sort->size -= 1;
	DEBUG_VAR(data, "to_sort->size", "decreased by 1");
	DEBUG_LINE(data, __LINE__);
	
	DEBUG_FUNC_EXIT(data);
}
