/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:02 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:45:17 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

int	chunk_value(t_ps *data, t_chunk *chunk, int n)
{
	t_loc	loc;
	t_stack	*stk;
	int		i;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== CHUNK_VALUE START ===");
	debug_log(DEBUG_DEBUG, "chunk->loc=%d, chunk->size=%d, n=%d", chunk->loc, chunk->size, n);
	
	loc = chunk->loc;
	stk = loc_to_stack(data, loc);
	
	debug_log(DEBUG_DEBUG, "Selected stack: %s", (loc == TOP_A || loc == BOTTOM_A) ? "A" : "B");
	debug_log(DEBUG_DEBUG, "Stack: top=%d, bottom=%d, size=%d", stk->top, stk->bottom, stk->size);
	
	if (loc == TOP_A || loc == TOP_B)
		i = stk->top;
	else if (loc == BOTTOM_A || loc == BOTTOM_B)
		i = stk->bottom;
	else
		i = stk->top; // Default fallback
	
	debug_log(DEBUG_DEBUG, "Starting index: i=%d", i);
	
	if (loc == TOP_A || loc == TOP_B)
	{
		debug_log(DEBUG_DEBUG, "Entering while (--n > 0) loop for TOP_A/TOP_B with n=%d", n);
		while (--n > 0)
		{
			debug_log(DEBUG_DEBUG, "Decrementing n: n=%d, moving down from i=%d", n, i);
			i = next_down(stk, i);
			debug_log(DEBUG_DEBUG, "After next_down: i=%d", i);
		}
		debug_log(DEBUG_DEBUG, "Exited while loop, final i=%d", i);
	}
	else if (loc == BOTTOM_A || loc == BOTTOM_B)
	{
		debug_log(DEBUG_DEBUG, "Entering while (--n > 0) loop for BOTTOM_A/BOTTOM_B with n=%d", n);
		while (--n > 0)
		{
			debug_log(DEBUG_DEBUG, "Decrementing n: n=%d, moving up from i=%d", n, i);
			i = next_up(stk, i);
			debug_log(DEBUG_DEBUG, "After next_up: i=%d", i);
		}
		debug_log(DEBUG_DEBUG, "Exited while loop, final i=%d", i);
	}
	
	debug_log(DEBUG_DEBUG, "Final index: i=%d, value=%d", i, stk->stack[i]);
	debug_log(DEBUG_DEBUG, "=== CHUNK_VALUE END ===");
	
	return (stk->stack[i]);
}

int	chunk_max_value(t_ps *data, t_chunk *chunk)
{
	t_stack	*stk;
	int		size;
	int		max_value;
	int		i;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== CHUNK_MAX_VALUE START ===");
	debug_log(DEBUG_DEBUG, "chunk->loc=%d, chunk->size=%d", chunk->loc, chunk->size);
	
	stk = loc_to_stack(data, chunk->loc);
	size = chunk->size;
	max_value = 0;
	
	debug_log(DEBUG_DEBUG, "Selected stack: %s", (chunk->loc == TOP_A || chunk->loc == BOTTOM_A) ? "A" : "B");
	debug_log(DEBUG_DEBUG, "Stack: top=%d, bottom=%d, size=%d", stk->top, stk->bottom, stk->size);
	
	if (chunk->loc == TOP_A || chunk->loc == TOP_B)
		i = stk->top;
	else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
		i = stk->bottom;
	else
		i = stk->top; // Default fallback
	
	debug_log(DEBUG_DEBUG, "Starting index: i=%d", i);
	debug_log(DEBUG_DEBUG, "Starting size: %d", size);
	
	while (size--)
	{
		debug_log(DEBUG_DEBUG, "Checking index %d: value=%d, current max=%d", i, stk->stack[i], max_value);
		
		if (stk->stack[i] > max_value)
		{
			max_value = stk->stack[i];
			debug_log(DEBUG_DEBUG, "New max value: %d", max_value);
		}
		
		if (chunk->loc == TOP_A || chunk->loc == TOP_B)
			i = next_down(stk, i);
		else if (chunk->loc == BOTTOM_A || chunk->loc == BOTTOM_B)
			i = next_up(stk, i);
	}
	
	debug_log(DEBUG_DEBUG, "Final max value: %d", max_value);
	debug_log(DEBUG_DEBUG, "=== CHUNK_MAX_VALUE END ===");
	
	return (max_value);
}

t_stack	*loc_to_stack(t_ps *data, t_loc loc)
{
	if (loc == TOP_A || loc == BOTTOM_A)
		return (&data->a);
	else
		return (&data->b);
}
