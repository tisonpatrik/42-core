/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_shaping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:29:33 by ptison            #+#    #+#             */
/*   Updated: 2025/10/05 20:31:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

static size_t	calculate_lis_length(t_node **lis_nodes)
{
	size_t	count;

	count = 0;
	while (lis_nodes[count] != NULL)
		count++;
	return (count);
}

static bool	is_node_in_lis(t_node *node, t_node **lis_nodes, size_t lis_count)
{
	size_t	i;

	if (!node || !lis_nodes)
		return (false);
	i = 0;
	while (i < lis_count)
	{
		if (lis_nodes[i] == node)
			return (true);
		i++;
	}
	return (false);
}

/*
 * Resets the B shaping state variables to their initial values.
 * This ensures clean state for each new sorting operation.
 *
 * @param state: The sorting state containing the shaping variables
 */
static void	reset_b_shaping(t_sorting_state *state)
{
	state->min_b = 0;
	state->max_b = 0;
	state->has_b_range = false;
}

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
 * - Tracking the range of values in B using state variables
 * - Calculating the midpoint between min and max values
 * - Rotating smaller elements to the bottom to keep larger elements near the
 * top
 * - This facilitates easier insertion during the merging phase
 *
 * @param state: The sorting state containing both stacks and shaping variables
 */
static void	apply_shaping(t_sorting_state *state)
{
	if (get_size(state->b) < 2)
		return ;
	update_b_range(state->b->head->content, &state->min_b, &state->max_b,
		&state->has_b_range);
	if (state->b->head->content < (state->min_b + state->max_b) / 2)
		rotate_b(state);
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
	size_t	pushes_total;
	bool	enable_shaping;

	lis_count = calculate_lis_length(lis_nodes);
	reset_b_shaping(state);
	pushes_total = (size_a > (int)lis_count) ? (size_a - (int)lis_count) : 0;
	enable_shaping = (pushes_total >= 3);
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
			if (enable_shaping)
				apply_shaping(state);
		}
		i++;
	}
}

/*
 * Counts the number of "breaks" (inversions) in a circular stack.
 * A break occurs when current element > next element (circularly).
 *
 * @param a: Stack to analyze
 * @return: Number of breaks/inversions
 */
int	count_breaks(t_stack *a)
{
	int		n;
	t_node	*cur;
	int		breaks;
	int		i;
	int		v;
	int		nv;

	n = get_size(a);
	if (n <= 1)
		return (0);
	cur = get_head(a);
	breaks = 0;
	i = 0;
	while (i < n)
	{
		v = cur->content;
		if (i == n - 1)
			nv = get_head(a)->content;
		else
			nv = get_next(cur)->content;
		if (v > nv)
			breaks++;
		cur = get_next(cur);
		i++;
	}
	return (breaks);
}

/*
 * Implements reverse chain mode as a fallback when LIS is too short.
 * This mode only does separation: keeps minimum in A,
	pushes everything else to B.
 * The standard reinsertion phase will handle merging B back to A.
 *
 * Algorithm:
 * 1. Rotate minimum in A to the top (cheapest direction)
 * 2. Push all other elements to B (without shaping)
 * 3. Return - let standard reinsertion handle B->A merge
 *
 * @param state: The sorting state containing both stacks
 */
void	reverse_chain_mode(t_sorting_state *state)
{
	int	n;
	int	idx_min_a;
	int	k;

	n = get_size(state->a);
	if (n <= 1)
		return ;
	idx_min_a = find_min_index(state->a);
	if (idx_min_a <= n / 2)
	{
		k = 0;
		while (k < idx_min_a)
		{
			rotate_a(state);
			k++;
		}
	}
	else
	{
		k = idx_min_a;
		while (k < n)
		{
			reverse_rotate_a(state);
			k++;
		}
	}
	while (get_size(state->a) > 1)
		push_b(state);
}
