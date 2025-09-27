/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:29 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ops.h"
#include "../../include/separator.h"
#include <stdbool.h>

/*
 * Updates the range tracking for stack B values.
 * Maintains min and max values to enable mid-point calculations for shaping.
 *
 * @param value: The new value to consider for range tracking
 * @param min_b: Pointer to current minimum value in B
 * @param max_b: Pointer to current maximum value in B
 * @param has_b_range: Pointer to flag indicating if range has been initialized
 */
static void	update_b_range(int value, int *min_b, int *max_b, bool *has_b_range)
{
	if (*has_b_range == false)
	{
		*min_b = value;
		*max_b = value;
		*has_b_range = true;
	}
	else
	{
		if (value < *min_b)
			*min_b = value;
		if (value > *max_b)
			*max_b = value;
	}
}

/*
 * Applies shaping algorithm to maintain stack B in a semi-sorted state.
 *
 * The shaping algorithm maintains stack B by:
 * - Tracking the range of values in B using static variables
 * - Calculating the midpoint between min and max values
 * - Rotating smaller elements to the bottom to keep larger elements near the
 * top
 * - This facilitates easier insertion during the merging phase
 *
 * @param state: The sorting state containing both stacks
 */
static void	apply_shaping(t_sorting_state *state)
{
	static int	min_b = 0;
	static int	max_b = 0;
	static bool	has_b_range = false;
	int			mid;
	int			value;

	value = state->b->head->content;
	update_b_range(value, &min_b, &max_b, &has_b_range);
	mid = (min_b + max_b) / 2;
	if (value < mid)
	{
		rotate_b(state);
	}
}

/*
 * Processes each element in stack A to implement the core separation logic.
 *
 * This function implements the fundamental principle: "Keep what's already
 * sorted, move what needs sorting." For each element:
 * - If element is in LIS: rotate_a() to keep it in A
 * - If element is not in LIS: push_b() to move to B, then apply shaping
 *
 * @param state: The sorting state containing both stacks
 * @param size_a: Number of elements originally in stack A
 * @param lis_nodes: Array of nodes that form the longest increasing subsequence
 */
void	process_stack_elements(t_sorting_state *state, int size_a,
		t_node **lis_nodes)
{
	int		i;
	t_node	*current;
	size_t	lis_count;

	lis_count = calculate_lis_length(lis_nodes);
	i = 0;
	while (i < size_a)
	{
		current = state->a->head;
		if (is_node_in_lis(current, lis_nodes, lis_count))
		{
			rotate_a(state);
		}
		else
		{
			push_b(state);
			apply_shaping(state);
		}
		i++;
	}
}

/*
 * Entry point for the separator module.
 *
 * This function orchestrates the entire separation process:
 * 1. Validates input and handles edge cases (size <= 3)
 * 2. Allocates memory arena for LIS computation
 * 3. Computes the longest increasing subsequence
 * 4. Processes stack elements to separate LIS from non-LIS elements
 * 5. Cleans up allocated memory
 *
 * @param state: The sorting state containing both stacks
 */
void	push_non_lis_into_b(t_sorting_state *state)
{
	t_separator_arena	*arena;
	t_node				**lis_nodes;
	int					size_a;

	if (!state || !state->a)
		return ;
	size_a = get_size(state->a);
	if (size_a <= 3)
		return ;
	arena = allocate_separator_arena(size_a);
	if (!arena)
		return ;
	lis_nodes = get_lis_nodes(state->a, arena);
	if (!lis_nodes)
	{
		free_separator_arena(arena);
		return ;
	}
	process_stack_elements(state, size_a, lis_nodes);
	free_separator_arena(arena);
}
