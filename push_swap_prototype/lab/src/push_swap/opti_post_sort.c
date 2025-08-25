/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_post_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:19 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:45:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	post_sort_optimization(t_ps *data)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== POST_SORT_OPTIMIZATION START ===");
	
	if (!data->op_list)
	{
		debug_log(DEBUG_DEBUG, "No operation list, returning early");
		return ;
	}
	
	debug_log(DEBUG_DEBUG, "Calling eliminate_neutral_op");
	eliminate_neutral_op(data->op_list);
	
	debug_log(DEBUG_DEBUG, "Calling merge_op");
	merge_op(data->op_list);
	
	debug_log(DEBUG_DEBUG, "=== POST_SORT_OPTIMIZATION END ===");
}

void	eliminate_neutral_op(t_list *op_list)
{
	t_list	*ref;
	t_list	*cmp;
	t_op	op_neutral;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== ELIMINATE_NEUTRAL_OP START ===");
	
	ref = op_list->next;
	debug_log(DEBUG_DEBUG, "Starting with ref = op_list->next");
	
	while (ref && ref->next)
	{
		debug_log(DEBUG_DEBUG, "Processing ref operation: %d", op_from(ref));
		
		op_neutral = neutral_op(op_from(ref));
		debug_log(DEBUG_DEBUG, "neutral_op returned: %d", op_neutral);
		
		if (op_neutral)
		{
			debug_log(DEBUG_DEBUG, "Found neutral operation, looking for matching operation");
			
			cmp = ref->next;
			debug_log(DEBUG_DEBUG, "Starting comparison from ref->next");
			
			while (!op_on_same_stack(op_from(ref), op_from(cmp))
				&& op_from(cmp) != op_neutral && cmp->next)
			{
				debug_log(DEBUG_DEBUG, "Skipping operation %d (not on same stack or not neutral)", op_from(cmp));
				cmp = cmp->next;
			}
			
			debug_log(DEBUG_DEBUG, "Found comparison operation: %d", op_from(cmp));
			
			if (ref->prev && op_from(cmp) == op_neutral)
			{
				debug_log(DEBUG_DEBUG, "Found neutral pair, removing operations");
				ref = ref->prev;
				remove_op(ref->next);
				remove_op(cmp);
				continue ;
			}
		}
		ref = ref->next;
	}
	
	debug_log(DEBUG_DEBUG, "=== ELIMINATE_NEUTRAL_OP END ===");
}

void	merge_op(t_list *op_list)
{
	t_list	*reader;
	t_op	child;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== MERGE_OP START ===");
	
	reader = op_list;
	debug_log(DEBUG_DEBUG, "Starting with reader = op_list");
	
	while (reader && reader->next)
	{
		debug_log(DEBUG_DEBUG, "Processing operations: %d and %d", op_from(reader), op_from(reader->next));
		
		child = child_op(op_from(reader), op_from(reader->next));
		debug_log(DEBUG_DEBUG, "child_op returned: %d", child);
		
		if (child)
		{
			debug_log(DEBUG_DEBUG, "Found mergeable operations, merging into: %d", child);
			remove_op(reader->next);
			reader->content = (void *)(uintptr_t)child;
		}
		else
		{
			debug_log(DEBUG_DEBUG, "Operations not mergeable");
		}
		
		reader = reader->next;
	}
	
	debug_log(DEBUG_DEBUG, "=== MERGE_OP END ===");
}
