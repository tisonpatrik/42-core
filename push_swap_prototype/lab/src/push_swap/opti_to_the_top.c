/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_to_the_top.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:20 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:43:57 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	chunk_to_the_top(t_ps *data, t_chunk *to_sort)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== CHUNK_TO_THE_TOP START ===");
	debug_log_chunk_state(to_sort, "to_sort at entry");
	debug_log(DEBUG_DEBUG, "Stack A size: %d, Stack B size: %d", current_size(&data->a), current_size(&data->b));
	
	if (to_sort->loc == BOTTOM_B && current_size(&data->b) == to_sort->size)
	{
		debug_log(DEBUG_DEBUG, "Case 1: BOTTOM_B -> TOP_B (size matches)");
		to_sort->loc = TOP_B;
	}
	if (to_sort->loc == BOTTOM_A && current_size(&data->a) == to_sort->size)
	{
		debug_log(DEBUG_DEBUG, "Case 2: BOTTOM_A -> TOP_A (size matches)");
		to_sort->loc = TOP_A;
	}
	
	// Debug: Log function exit
	debug_log_chunk_state(to_sort, "to_sort at exit");
	debug_log(DEBUG_DEBUG, "=== CHUNK_TO_THE_TOP END ===");
}
