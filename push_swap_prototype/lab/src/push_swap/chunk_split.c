/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:57:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/24 18:49:05 by patrik           ###   ########.fr       */
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

	// Debug logging - function entry
	DEBUG_FUNC_ENTRY(data);
	
	// Log chunk information
	debug_log(DEBUG_DEBUG, "Splitting chunk: loc=%d, size=%d", to_split->loc, to_split->size);
	debug_log_chunk_state(to_split, "input chunk");

	innit_size(&dest->min, &dest->mid, &dest->max);
	set_split_loc(to_split->loc, &dest->min, &dest->mid, &dest->max);
	set_third_pivots(to_split->loc, to_split->size, &pivot_1, &pivot_2);
	
	// Log pivot information
	debug_log(DEBUG_DEBUG, "Pivots calculated: pivot_1=%d, pivot_2=%d", pivot_1, pivot_2);
	
	max_value = chunk_max_value(data, to_split);
	debug_log(DEBUG_DEBUG, "Max value in chunk: %d", max_value);
	
	while (to_split->size--)
	{
		next_value = chunk_value(data, to_split, 1);
		if (next_value > max_value - pivot_2)
		{
			debug_log(DEBUG_TRACE, "Moving %d to MAX chunk (dest: %d)", next_value, dest->max.loc);
			dest->max.size += move_from_to(data, to_split->loc, dest->max.loc);
			split_max_reduction(data, &dest->max);
			if (a_partly_sort(data, 1) && to_split->size)
				easy_sort(data, to_split);
		}
		else if (next_value > max_value - pivot_1)
		{
			debug_log(DEBUG_TRACE, "Moving %d to MID chunk (dest: %d)", next_value, dest->mid.loc);
			dest->mid.size += move_from_to(data, to_split->loc, dest->mid.loc);
		}
		else
		{
			debug_log(DEBUG_TRACE, "Moving %d to MIN chunk (dest: %d)", next_value, dest->min.loc);
			dest->min.size += move_from_to(data, to_split->loc, dest->min.loc);
		}
	}
	
	// Log final chunk sizes
	debug_log(DEBUG_DEBUG, "Chunk split completed:");
	debug_log(DEBUG_DEBUG, "  MIN chunk: loc=%d, size=%d", dest->min.loc, dest->min.size);
	debug_log(DEBUG_DEBUG, "  MID chunk: loc=%d, size=%d", dest->mid.loc, dest->mid.size);
	debug_log(DEBUG_DEBUG, "  MAX chunk: loc=%d, size=%d", dest->max.loc, dest->max.size);
	
	// Debug logging - function exit
	DEBUG_FUNC_EXIT(data);
}

void	innit_size(t_chunk *min, t_chunk *mid, t_chunk *max)
{
	min->size = 0;
	mid->size = 0;
	max->size = 0;
}

void	set_split_loc(t_loc loc, t_chunk *min, t_chunk *mid, t_chunk *max)
{
	if (loc == TOP_A)
	{
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = BOTTOM_A;
	}
	else if (loc == BOTTOM_A)
	{
		min->loc = BOTTOM_B;
		mid->loc = TOP_B;
		max->loc = TOP_A;
	}
	else if (loc == TOP_B)
	{
		min->loc = BOTTOM_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
	}
	else if (loc == BOTTOM_B)
	{
		min->loc = TOP_B;
		mid->loc = BOTTOM_A;
		max->loc = TOP_A;
	}
}

void	set_third_pivots(t_loc loc, int crt_size, int *pivot_1, int *pivot_2)
{
	// Initialize pivot_2 first
	*pivot_2 = crt_size / 3;
	
	// Initialize pivot_1 based on location
	if (loc == TOP_A || loc == BOTTOM_A)
	{
		*pivot_1 = 2 * crt_size / 3;
		// Special case for small chunks
		if (crt_size < 15)
			*pivot_1 = crt_size;
	}
	else if (loc == TOP_B || loc == BOTTOM_B)
	{
		*pivot_1 = crt_size / 2;
		// Special case for bottom B with small chunks
		if (loc == BOTTOM_B && crt_size < 8)
			*pivot_2 = crt_size / 2;
	}
	else
	{
		// Fallback initialization for any unexpected location values
		*pivot_1 = crt_size / 2;
	}
}
