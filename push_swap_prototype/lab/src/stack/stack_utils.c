/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:09:14 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:45:17 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/stack.h"
#include "../../include/debug_logging.h"

int	next_up(t_stack *stk, int index)
{
	if (current_size(stk) == 0)
		return (index);
	if (index == 0)
		return (stk->size - 1);
	else
		return (index - 1);
}

int	next_down(t_stack *stk, int index)
{
	if (current_size(stk) == 0)
		return (index);
	if (index == stk->size - 1)
		return (0);
	else
		return (index + 1);
}

int	value(t_stack *stk, int n)
{
	int	i;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== VALUE START ===");
	debug_log(DEBUG_DEBUG, "n=%d, stk->top=%d, stk->size=%d", n, stk->top, stk->size);

	i = stk->top;
	debug_log(DEBUG_DEBUG, "Starting index: i=%d", i);
	
	debug_log(DEBUG_DEBUG, "Entering while (--n > 0) loop with n=%d", n);
	while (--n > 0)
	{
		debug_log(DEBUG_DEBUG, "Decrementing n: n=%d, moving down from i=%d", n, i);
		i = next_down(stk, i);
		debug_log(DEBUG_DEBUG, "After next_down: i=%d", i);
	}
	debug_log(DEBUG_DEBUG, "Exited while loop, final i=%d, value=%d", i, stk->stack[i]);
	
	debug_log(DEBUG_DEBUG, "=== VALUE END ===");
	return (stk->stack[i]);
}

int	current_size(t_stack *stk)
{
	if (stk->top == stk->bottom && stk->stack[stk->top] == 0)
		return (0);
	if (stk->top > stk->bottom)
		return ((stk->size - stk->top) + (stk->bottom + 1));
	else
		return (stk->bottom - stk->top + 1);
}

bool	is_full(t_stack *stk)
{
	return (stk->size == current_size(stk));
}
