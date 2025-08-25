/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:56:55 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 11:01:26 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	chunk_sort(t_ps *data)
{
	t_chunk	chunk_all;

	chunk_all.loc = TOP_A;
	chunk_all.size = data->a.size;
	rec_chunk_sort(data, &chunk_all);
}

void	rec_chunk_sort(t_ps *data, t_chunk *to_sort)
{
	t_split_dest	dest;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== REC_CHUNK_SORT START ===");
	debug_log_chunk_state(to_sort, "to_sort at entry");
	debug_log(DEBUG_DEBUG, "to_sort->size = %d", to_sort->size);

	chunk_to_the_top(data, to_sort);
	debug_log(DEBUG_DEBUG, "After chunk_to_the_top: to_sort->loc=%d, to_sort->size=%d", to_sort->loc, to_sort->size);
	
	easy_sort(data, to_sort);
	debug_log(DEBUG_DEBUG, "After easy_sort: to_sort->loc=%d, to_sort->size=%d", to_sort->loc, to_sort->size);

	// Debug: Log before size check
	debug_log(DEBUG_DEBUG, "Before size check: to_sort->size = %d", to_sort->size);
	
	if (to_sort->size <= 3)
	{
		debug_log(DEBUG_DEBUG, "Size <= 3, processing directly");
		
		if (to_sort->size == 3)
		{
			debug_log(DEBUG_DEBUG, "Calling sort_three");
			sort_three(data, to_sort);
		}
		else if (to_sort->size == 2)
		{
			debug_log(DEBUG_DEBUG, "Calling sort_two");
			sort_two(data, to_sort);
		}
		else if (to_sort->size == 1)
		{
			debug_log(DEBUG_DEBUG, "Calling sort_one");
			sort_one(data, to_sort);
		}
		debug_log(DEBUG_DEBUG, "=== REC_CHUNK_SORT END (size <= 3) ===");
		return ;
	}
	
	debug_log(DEBUG_DEBUG, "Size > 3, calling chunk_split");
	chunk_split(data, to_sort, &dest);
	
	// Debug: Log destination chunks after split
	debug_log(DEBUG_DEBUG, "After chunk_split:");
	debug_log_chunk_state(&dest.max, "dest.max");
	debug_log_chunk_state(&dest.mid, "dest.mid");
	debug_log_chunk_state(&dest.min, "dest.min");
	
	debug_log(DEBUG_DEBUG, "Calling rec_chunk_sort with dest.max");
	rec_chunk_sort(data, &dest.max);
	
	debug_log(DEBUG_DEBUG, "Calling rec_chunk_sort with dest.mid");
	rec_chunk_sort(data, &dest.mid);
	
	debug_log(DEBUG_DEBUG, "Calling rec_chunk_sort with dest.min");
	rec_chunk_sort(data, &dest.min);
	
	debug_log(DEBUG_DEBUG, "=== REC_CHUNK_SORT END (recursive) ===");
}

void	sort_two(t_ps *data, t_chunk *to_sort)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SORT_TWO START ===");
	debug_log_chunk_state(to_sort, "to_sort at entry");

	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		debug_log(DEBUG_DEBUG, "Case: to_sort->loc != TOP_A, calling move_from_to twice");
		debug_log(DEBUG_DEBUG, "First move_from_to: %d -> TOP_A", to_sort->loc);
		move_from_to(data, to_sort->loc, TOP_A);
		debug_log(DEBUG_DEBUG, "Second move_from_to: %d -> TOP_A", to_sort->loc);
		move_from_to(data, to_sort->loc, TOP_A);
	}
	else
	{
		debug_log(DEBUG_DEBUG, "Case: to_sort->loc == TOP_A, no move_from_to needed");
	}
	
	debug_log(DEBUG_DEBUG, "Checking if value(&data->a, 1) > value(&data->a, 2)");
	debug_log(DEBUG_DEBUG, "value(&data->a, 1) = %d, value(&data->a, 2) = %d", value(&data->a, 1), value(&data->a, 2));
	
	if (value(&data->a, 1) > value(&data->a, 2))
	{
		debug_log(DEBUG_DEBUG, "Values are not in order, calling swap_a");
		swap_a(data);
	}
	else
	{
		debug_log(DEBUG_DEBUG, "Values are already in order, no swap needed");
	}
	
	to_sort->size -= 2;
	debug_log(DEBUG_DEBUG, "Decremented to_sort->size by 2, new size = %d", to_sort->size);
	
	debug_log(DEBUG_DEBUG, "=== SORT_TWO END ===");
}

void	sort_one(t_ps *data, t_chunk *to_sort)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SORT_ONE START ===");
	debug_log_chunk_state(to_sort, "to_sort at entry");
	
	if (to_sort->loc == BOTTOM_A || to_sort->loc == BOTTOM_B
		|| to_sort->loc == TOP_B)
	{
		debug_log(DEBUG_DEBUG, "Case: to_sort->loc != TOP_A, calling move_from_to");
		debug_log(DEBUG_DEBUG, "move_from_to: %d -> TOP_A", to_sort->loc);
		move_from_to(data, to_sort->loc, TOP_A);
	}
	else
	{
		debug_log(DEBUG_DEBUG, "Case: to_sort->loc == TOP_A, no move_from_to needed");
	}
	
	to_sort->size -= 1;
	debug_log(DEBUG_DEBUG, "Decremented to_sort->size by 1, new size = %d", to_sort->size);
	
	debug_log(DEBUG_DEBUG, "=== SORT_ONE END ===");
}
