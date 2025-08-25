/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:57:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 11:18:49 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest)
{
	int	pivot_1;
	int	pivot_2;
	int	max_value;
	int	next_value;

	// Debug: Log initial state
	debug_log(DEBUG_DEBUG, "=== CHUNK_SPLIT START ===");
	debug_log_chunk_state(to_split, "initial to_split");
	debug_log(DEBUG_DEBUG, "Initial to_split->size = %d", to_split->size);

	innit_size(&dest->min, &dest->mid, &dest->max);
	set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
	set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
	
	// Debug: Log pivot values
	debug_log(DEBUG_DEBUG, "Pivot values: pivot1=%d, pivot2=%d", pivot_1, pivot_2);
	
	max_value = chunk_max_value(data, to_split);
	debug_log(DEBUG_DEBUG, "Max value = %d", max_value);
	
	// Debug: Log before while loop
	debug_log(DEBUG_DEBUG, "Before while loop: to_split->size = %d", to_split->size);
	
	while (to_split->size > 0)
	{
		to_split->size--;
		// Debug: Log each iteration
		debug_log(DEBUG_DEBUG, "=== WHILE LOOP ITERATION ===");
		debug_log(DEBUG_DEBUG, "After size--: to_split->size = %d", to_split->size + 1);
		debug_log(DEBUG_DEBUG, "Current to_split->size = %d", to_split->size);
		
		next_value = chunk_value(data, to_split, 1);
		debug_log(DEBUG_DEBUG, "next_value = %d (from chunk_value with size=%d)", next_value, to_split->size + 1);
		
		if (next_value > max_value - pivot_2)
		{
			debug_log(DEBUG_DEBUG, "Case 1: next_value > max_value - pivot2 (%d > %d)", next_value, max_value - pivot_2);
			dest->max.size += move_from_to(data, to_split->loc, dest->max.loc);
			split_max_reduction(data, &dest->max);
			if (a_partly_sort(data, 1) && to_split->size)
				easy_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
		{
			debug_log(DEBUG_DEBUG, "Case 2: next_value > max_value - pivot1 (%d > %d)", next_value, max_value - pivot_1);
			dest->mid.size += move_from_to(data, to_split->loc, dest->mid.loc);
		}
		else
		{
			debug_log(DEBUG_DEBUG, "Case 3: else case");
			dest->min.size += move_from_to(data, to_split->loc, dest->min.loc);
		}
		
		// Debug: Log destination chunk sizes after this iteration
		debug_log(DEBUG_DEBUG, "After iteration: dest->min.size=%d, dest->mid.size=%d, dest->max.size=%d", 
				 dest->min.size, dest->mid.size, dest->max.size);
	}
	
	// Debug: Log final state
	debug_log(DEBUG_DEBUG, "=== CHUNK_SPLIT END ===");
	debug_log(DEBUG_DEBUG, "Final to_split->size = %d", to_split->size);
	debug_log(DEBUG_DEBUG, "Final dest sizes: min=%d, mid=%d, max=%d", 
			 dest->min.size, dest->mid.size, dest->max.size);
}

void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== INNIT_SIZE START ===");
	
	min->size = 0;
	mid->size = 0;
	max->size = 0;
	
	debug_log(DEBUG_DEBUG, "Initialized: min->size=%d, mid->size=%d, max->size=%d", min->size, mid->size, max->size);
	debug_log(DEBUG_DEBUG, "=== INNIT_SIZE END ===");
}

void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SET_SPLIT_LOC START ===");
	debug_log(DEBUG_DEBUG, "Input loc=%d", loc);
	
	if (loc == TOP_A)
	{
		debug_log(DEBUG_DEBUG, "Case: TOP_A");
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = BOTTOM_A;
		debug_log(DEBUG_DEBUG, "Set: min->loc=%d, mid->loc=%d, max->loc=%d", min->loc, mid->loc, max->loc);
	}
	else if (loc == BOTTOM_A)
	{
		debug_log(DEBUG_DEBUG, "Case: BOTTOM_A");
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = TOP_A;
		debug_log(DEBUG_DEBUG, "Set: min->loc=%d, mid->loc=%d, max->loc=%d", min->loc, mid->loc, max->loc);
	}
	else if (loc == TOP_B)
	{
		debug_log(DEBUG_DEBUG, "Case: TOP_B");
		min->loc = BOTTOM_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
		debug_log(DEBUG_DEBUG, "Set: min->loc=%d, mid->loc=%d, max->loc=%d", min->loc, mid->loc, max->loc);
	}
	else if (loc == BOTTOM_B)
	{
		debug_log(DEBUG_DEBUG, "Case: BOTTOM_B");
		min->loc = TOP_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
		debug_log(DEBUG_DEBUG, "Set: min->loc=%d, mid->loc=%d, max->loc=%d", min->loc, mid->loc, max->loc);
	}
	
	debug_log(DEBUG_DEBUG, "=== SET_SPLIT_LOC END ===");
}

void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SET_THIRD_PIVOTS START ===");
	debug_log(DEBUG_DEBUG, "loc=%d, crt_size=%d", loc, crt_size);
	
	// Initialize pivot_2 first
	*pivot_2 = crt_size / 3;
	debug_log(DEBUG_DEBUG, "Initial pivot_2 = %d", *pivot_2);
	
	// Initialize pivot_1 based on location
	if (loc == TOP_A || loc == BOTTOM_A)
	{
		debug_log(DEBUG_DEBUG, "Case: TOP_A or BOTTOM_A");
		*pivot_1 = 2 * crt_size / 3;
		debug_log(DEBUG_DEBUG, "pivot_1 = 2 * %d / 3 = %d", crt_size, *pivot_1);
		
		// Special case for small chunks
		if (crt_size < 15)
		{
			*pivot_1 = crt_size;
			debug_log(DEBUG_DEBUG, "Special case: crt_size < 15, pivot_1 = %d", *pivot_1);
		}
	}
	else if (loc == TOP_B || loc == BOTTOM_B)
	{
		debug_log(DEBUG_DEBUG, "Case: TOP_B or BOTTOM_B");
		*pivot_1 = crt_size / 2;
		debug_log(DEBUG_DEBUG, "pivot_1 = %d / 2 = %d", crt_size, *pivot_1);
		
		// Special case for bottom B with small chunks
		if (loc == BOTTOM_B && crt_size < 8)
		{
			*pivot_2 = crt_size / 2;
			debug_log(DEBUG_DEBUG, "Special case: BOTTOM_B and crt_size < 8, pivot_2 = %d", *pivot_2);
		}
	}
	else
	{
		// Fallback initialization for any unexpected location values
		debug_log(DEBUG_DEBUG, "Case: fallback (unexpected location)");
		*pivot_1 = crt_size / 2;
		debug_log(DEBUG_DEBUG, "pivot_1 = %d / 2 = %d", crt_size, *pivot_1);
	}
	
	debug_log(DEBUG_DEBUG, "Final pivots: pivot_1=%d, pivot_2=%d", *pivot_1, *pivot_2);
	debug_log(DEBUG_DEBUG, "=== SET_THIRD_PIVOTS END ===");
}
