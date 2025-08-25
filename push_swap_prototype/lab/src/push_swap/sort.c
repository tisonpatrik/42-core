/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:28 by ugerkens          #+#    #+#             */
/*   Updated: 2025/08/25 00:43:57 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include "../../include/debug_logging.h"

void	sort(t_ps *data)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SORT START ===");
	debug_log(DEBUG_DEBUG, "Stack A size: %d", data->a.size);
	debug_log(DEBUG_DEBUG, "Is sorted: %s", is_sorted(data) ? "true" : "false");
	
	if (data->a.size <= 1 || is_sorted(data))
	{
		debug_log(DEBUG_DEBUG, "Early return: size <= 1 or already sorted");
		return ;
	}
	else if (data->a.size == 3)
	{
		debug_log(DEBUG_DEBUG, "Case: size == 3, calling sort_three_a");
		sort_three_a(data);
	}
	else if (data->a.size == 5)
	{
		debug_log(DEBUG_DEBUG, "Case: size == 5, calling sort_five_a");
		sort_five_a(data);
	}
	else
	{
		debug_log(DEBUG_DEBUG, "Case: size > 5, calling chunk_sort");
		chunk_sort(data);
	}
	
	debug_log(DEBUG_DEBUG, "Calling post_sort_optimization");
	post_sort_optimization(data);
	
	debug_log(DEBUG_DEBUG, "=== SORT END ===");
}

void	sort_three_a(t_ps *data)
{
	int	first;
	int	second;
	int	third;

	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SORT_THREE_A START ===");
	debug_log(DEBUG_DEBUG, "Stack A size: %d", data->a.size);

	first = value(&data->a, 1);
	second = value(&data->a, 2);
	third = value(&data->a, 3);
	
	debug_log(DEBUG_DEBUG, "Values: first=%d, second=%d, third=%d", first, second, third);

	debug_log(DEBUG_DEBUG, "Checking condition 1: first > second && third > second && third > first");
	debug_log(DEBUG_DEBUG, "first > second: %s, third > second: %s, third > first: %s", 
			 first > second ? "true" : "false", third > second ? "true" : "false", third > first ? "true" : "false");
	
	if (first > second && third > second && third > first)
	{
		debug_log(DEBUG_DEBUG, "Condition 1 met: calling swap_a");
		swap_a(data);
	}
	else
	{
		debug_log(DEBUG_DEBUG, "Checking condition 2: first > second && third > second && first > third");
		debug_log(DEBUG_DEBUG, "first > third: %s", first > third ? "true" : "false");
		
		if (first > second && third > second && first > third)
		{
			debug_log(DEBUG_DEBUG, "Condition 2 met: calling rotate_a");
			rotate_a(data);
		}
		else
		{
			debug_log(DEBUG_DEBUG, "Checking condition 3: second > first && second > third && first > third");
			debug_log(DEBUG_DEBUG, "second > first: %s, second > third: %s, first > third: %s", 
					 second > first ? "true" : "false", second > third ? "true" : "false", first > third ? "true" : "false");
			
			if (second > first && second > third && first > third)
			{
				debug_log(DEBUG_DEBUG, "Condition_3 met: calling r_rotate_a");
				r_rotate_a(data);
			}
			else
			{
				debug_log(DEBUG_DEBUG, "Checking condition 4: second > first && second > third && third > first");
				debug_log(DEBUG_DEBUG, "third > first: %s", third > first ? "true" : "false");
				
				if (second > first && second > third && third > first)
				{
					debug_log(DEBUG_DEBUG, "Condition 4 met: calling swap_a + rotate_a");
					swap_a(data);
					rotate_a(data);
				}
				else
				{
					debug_log(DEBUG_DEBUG, "Checking condition 5: first > second && second > third && first > third");
					debug_log(DEBUG_DEBUG, "second > third: %s, first > third: %s", 
							 second > third ? "true" : "false", first > third ? "true" : "false");
					
					if (first > second && second > third && first > third)
					{
						debug_log(DEBUG_DEBUG, "Condition 5 met: calling swap_a + r_rotate_a");
						swap_a(data);
						r_rotate_a(data);
					}
					else
					{
						debug_log(DEBUG_DEBUG, "No conditions met: stack is already sorted");
					}
				}
			}
		}
	}
	
	debug_log(DEBUG_DEBUG, "=== SORT_THREE_A END ===");
}

void	sort_five_a(t_ps *data)
{
	// Debug: Log function entry
	debug_log(DEBUG_DEBUG, "=== SORT_FIVE_A START ===");
	debug_log(DEBUG_DEBUG, "Stack A size: %d, Stack B size: %d", current_size(&data->a), current_size(&data->b));

	debug_log(DEBUG_DEBUG, "Entering while loop: current_size(&data->a) > 3");
	while (current_size(&data->a) > 3)
	{
		debug_log(DEBUG_DEBUG, "Current stack A size: %d", current_size(&data->a));
		debug_log(DEBUG_DEBUG, "Checking if value(&data->a, 1) == 1 || value(&data->a, 1) == 2");
		debug_log(DEBUG_DEBUG, "value(&data->a, 1) = %d", value(&data->a, 1));

		if (value(&data->a, 1) == 1 || value(&data->a, 1) == 2)
		{
			debug_log(DEBUG_DEBUG, "Condition met: calling push_b");
			push_b(data);
		}
		else
		{
			debug_log(DEBUG_DEBUG, "Condition not met: calling rotate_a");
			rotate_a(data);
		}
	}
	
	debug_log(DEBUG_DEBUG, "Exited while loop, stack A size: %d", current_size(&data->a));
	debug_log(DEBUG_DEBUG, "Checking if value(&data->b, 1) < value(&data->b, 2)");
	debug_log(DEBUG_DEBUG, "value(&data->b, 1) = %d, value(&data->b, 2) = %d", value(&data->b, 1), value(&data->b, 2));
	
	if (value(&data->b, 1) < value(&data->b, 2))
	{
		debug_log(DEBUG_DEBUG, "Condition met: calling swap_b");
		swap_b(data);
	}
	else
	{
		debug_log(DEBUG_DEBUG, "Condition not met: no swap_b needed");
	}
	
	debug_log(DEBUG_DEBUG, "Calling sort_three_a");
	sort_three_a(data);
	
	debug_log(DEBUG_DEBUG, "Calling push_a (first)");
	push_a(data);
	
	debug_log(DEBUG_DEBUG, "Calling push_a (second)");
	push_a(data);

	debug_log(DEBUG_DEBUG, "=== SORT_FIVE_A END ===");
}
