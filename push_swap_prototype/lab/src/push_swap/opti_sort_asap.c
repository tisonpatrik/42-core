/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti_sort_asap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:58:30 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:43:57 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	split_max_reduction(t_ps *data, t_chunk *max)
{
	t_stack	*a;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SPLIT_MAX_REDUCTION START ===");
	debug_log_chunk_state(max, "max chunk at entry");

	a = &data->a;

	// Debug: Log first condition check
	debug_log(DEBUG_DEBUG, "Checking condition 1: max->loc == TOP_A && max->size == 3 && is_consecutive(...) && a_partly_sort(data, 4)");
	debug_log(DEBUG_DEBUG, "max->loc == TOP_A: %s", max->loc == TOP_A ? "true" : "false");
	debug_log(DEBUG_DEBUG, "max->size == 3: %s", max->size == 3 ? "true" : "false");
	
	if (max->loc == TOP_A && max->size == 3 && is_consecutive(value(a, 1),
			value(a, 2), value(a, 3), value(a, 4)) && a_partly_sort(data, 4))
	{
		debug_log(DEBUG_DEBUG, "Condition 1 met: calling sort_three");
		sort_three(data, max);
		debug_log(DEBUG_DEBUG, "=== SPLIT_MAX_REDUCTION END (early return) ===");
		return ;
	}
	
	// Debug: Log second condition check
	debug_log(DEBUG_DEBUG, "Checking condition 2: max->loc == TOP_A && value(a, 1) == value(a, 3) - 1 && a_partly_sort(data, 3)");
	debug_log(DEBUG_DEBUG, "value(a, 1) == value(a, 3) - 1: %s", value(a, 1) == value(a, 3) - 1 ? "true" : "false");
	
	if (max->loc == TOP_A && value(a, 1) == value(a, 3) - 1
		&& a_partly_sort(data, 3))
	{
		debug_log(DEBUG_DEBUG, "Condition 2 met: calling swap_a and decrementing max->size");
		swap_a(data);
		max->size--;
		debug_log(DEBUG_DEBUG, "After swap_a: max->size = %d", max->size);
	}
	
	// Debug: Log third condition check
	debug_log(DEBUG_DEBUG, "Checking condition 3: max->loc == TOP_A && a_partly_sort(data, 1)");
	
	if (max->loc == TOP_A && a_partly_sort(data, 1))
	{
		debug_log(DEBUG_DEBUG, "Condition 3 met: decrementing max->size");
		max->size--;
		debug_log(DEBUG_DEBUG, "After decrement: max->size = %d", max->size);
	}
	
	debug_log_chunk_state(max, "max chunk at exit");
	debug_log(DEBUG_DEBUG, "=== SPLIT_MAX_REDUCTION END ===");
}

bool	a_partly_sort(t_ps *data, int from)
{
	int		i;
	t_stack	*a;
	int		value;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== A_PARTLY_SORT START ===");
	debug_log(DEBUG_DEBUG, "from=%d, stack A size=%d", from, data->a.size);

	a = &data->a;
	
	i = a->top;
	debug_log(DEBUG_DEBUG, "Starting from top: i=%d", i);
	
	// Debug: Log the while (--from) loop
	debug_log(DEBUG_DEBUG, "Entering while (--from) loop with from=%d", from);
	while (--from)
	{
		debug_log(DEBUG_DEBUG, "Decrementing from: from=%d, moving down from i=%d", from, i);
		i = next_down(a, i);
		debug_log(DEBUG_DEBUG, "After next_down: i=%d", i);
	}
	debug_log(DEBUG_DEBUG, "Exited while (--from) loop, final i=%d", i);
	
	debug_log(DEBUG_DEBUG, "Entering main while loop: checking a->stack[i] != data->a.size");
	debug_log(DEBUG_DEBUG, "Current a->stack[i] = %d, data->a.size = %d", a->stack[i], data->a.size);
	
	while (a->stack[i] != data->a.size)
	{
		value = a->stack[i];
		debug_log(DEBUG_DEBUG, "Current value = %d at position i=%d", value, i);
		
		i = next_down(a, i);
		debug_log(DEBUG_DEBUG, "After next_down: i=%d", i);
		
		debug_log(DEBUG_DEBUG, "Checking if a->stack[i] == value + 1: %d == %d + 1", a->stack[i], value);
		if (a->stack[i] != value + 1)
		{
			debug_log(DEBUG_DEBUG, "NOT consecutive: a->stack[i] = %d, expected %d", a->stack[i], value + 1);
			debug_log(DEBUG_DEBUG, "=== A_PARTLY_SORT END (false) ===");
			return (false);
		}
		debug_log(DEBUG_DEBUG, "Consecutive: a->stack[i] = %d == %d + 1", a->stack[i], value);
	}
	
	debug_log(DEBUG_DEBUG, "All values are consecutive, returning true");
	debug_log(DEBUG_DEBUG, "=== A_PARTLY_SORT END (true) ===");
	return (true);
}

bool	is_consecutive(int a, int b, int c, int d)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== IS_CONSECUTIVE START ===");
	debug_log(DEBUG_DEBUG, "Input: a=%d, b=%d, c=%d, d=%d", a, b, c, d);
	
	sort_three_numbers(&a, &b, &c);
	debug_log(DEBUG_DEBUG, "After sort_three_numbers: a=%d, b=%d, c=%d, d=%d", a, b, c, d);
	
	bool result = ((b - a == 1) && (c - b == 1) && (d - c == 1));
	debug_log(DEBUG_DEBUG, "Checking: (b-a==1) && (c-b==1) && (d-c==1)");
	debug_log(DEBUG_DEBUG, "b-a=%d, c-b=%d, d-c=%d", b-a, c-b, d-c);
	debug_log(DEBUG_DEBUG, "Result: %s", result ? "true" : "false");
	
	debug_log(DEBUG_DEBUG, "=== IS_CONSECUTIVE END ===");
	return (result);
}

void	sort_three_numbers(int *a, int *b, int *c)
{
	int	temp;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SORT_THREE_NUMBERS START ===");
	debug_log(DEBUG_DEBUG, "Input: *a=%d, *b=%d, *c=%d", *a, *b, *c);

	if (*a > *b)
	{
		debug_log(DEBUG_DEBUG, "Swapping *a and *b: %d > %d", *a, *b);
		temp = *a;
		*a = *b;
		*b = temp;
		debug_log(DEBUG_DEBUG, "After swap: *a=%d, *b=%d", *a, *b);
	}
	if (*a > *c)
	{
		debug_log(DEBUG_DEBUG, "Swapping *a and *c: %d > %d", *a, *c);
		temp = *a;
		*a = *c;
		*c = temp;
		debug_log(DEBUG_DEBUG, "After swap: *a=%d, *c=%d", *a, *c);
	}
	if (*b > *c)
	{
		debug_log(DEBUG_DEBUG, "Swapping *b and *c: %d > %d", *b, *c);
		temp = *b;
		*b = *c;
		*c = temp;
		debug_log(DEBUG_DEBUG, "After swap: *b=%d, *c=%d", *b, *c);
	}
	
	debug_log(DEBUG_DEBUG, "Final result: *a=%d, *b=%d, *c=%d", *a, *b, *c);
	debug_log(DEBUG_DEBUG, "=== SORT_THREE_NUMBERS END ===");
}
