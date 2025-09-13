/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/13 14:13:29 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>



// Helper function to remove element at index from array (in-place)
static void	remove_element_at_index(int *array, int *size, int index)
{
	int	i;

	if (index < 0 || index >= *size)
		return;
	i = index;
	while (i < *size - 1)
	{
		array[i] = array[i + 1];
		i++;
	}
	(*size)--;
}

// Helper function to insert element at index into array (in-place)
static void	insert_element_at_index(int *array, int *size, int index, int value)
{
	int	i;

	if (index < 0 || index > *size)
		return;
	i = *size;
	while (i > index)
	{
		array[i] = array[i - 1];
		i--;
	}
	array[index] = value;
	(*size)++;
}


int get_break_points(int *a, int size) {
	if ( size <= 1) 
	{
		return 0;
	}
	
	int n = size;
	int breakpoints = 0;
	for (int i = 0; i < n-1; i++) {
		if (a[i] > a[i+1]) {
			breakpoints++;
		}
	}
	if (a[n-1] > a[0]) {
		breakpoints++;
	}
	return breakpoints;
}


int	get_estimatation(int *temp_a, int size, int size_penalty_factor, int heuristic_offset, int heuristic_divisor)
{
	int breakpoints = get_break_points(temp_a, size);
	int len = size;
	int size_penalty = len / size_penalty_factor;
	int	estimation = (breakpoints + size_penalty + heuristic_offset) / heuristic_divisor;

	return (estimation);
}

bool	get_better_position(t_position a, t_position b)
{
	return (better_position(a, b));
}

#include <stdio.h>
t_position	evaluate_with_lookahead(t_candidate *candidates, t_selector_arena *arena, t_move_direction direction)
{
	t_position	best_position;
	int			i;
	int			count;

	count = arena->top_k_count;
	if (count == 0)
	{
		best_position.total = INT_MAX;
		return (best_position);
	}
	best_position = candidates[0].position;
	int best_score = INT_MAX;
	i = 0;
	while (i < count)
	{
		t_position	position = candidates[i].position;
		int			rot = merged_cost(position.cost_a, position.cost_b);
		
	
		if (direction == MOVE_A_TO_B)
		{
			int	ia = normalize_index(arena->snapshot_arena->size_a, position.cost_a);
			int	ib = normalize_index(arena->snapshot_arena->size_b, position.cost_b);
			int	x = arena->snapshot_arena->a_values[ia];
			
			remove_element_at_index(arena->snapshot_arena->a_values, &arena->snapshot_arena->size_a, ia);
			insert_element_at_index(arena->snapshot_arena->b_values, &arena->snapshot_arena->size_b, ib, x);
			rot = rot + 1;
		}
		else
		{
			int	ib = normalize_index(arena->snapshot_arena->size_b, position.cost_b);
			int	ia = normalize_index(arena->snapshot_arena->size_a, position.cost_a);
			int	x = arena->snapshot_arena->b_values[ib];
			
			remove_element_at_index(arena->snapshot_arena->b_values, &arena->snapshot_arena->size_b, ib);
			insert_element_at_index(arena->snapshot_arena->a_values, &arena->snapshot_arena->size_a, ia, x);
			rot = rot + 1;
		}

		int heuristic_estimate = get_estimatation(arena->snapshot_arena->a_values, arena->snapshot_arena->size_a, arena->config.size_penalty_factor, arena->config.heuristic_offset, arena->config.heuristic_divisor);
		int total_score = heuristic_estimate + rot;
		if (total_score < best_score || (total_score == best_score && get_better_position(position, best_position)))
		{
			best_position = position;
			best_score = total_score;
		}
		i++;
	}

	
	// Debug: Print best_position values before returning
	printf("DEBUG lookahead_evaluator: best_position values:\n");
	printf("  total: %d\n", best_position.total);
	printf("  cost_a: %d\n", best_position.cost_a);
	printf("  cost_b: %d\n", best_position.cost_b);
	printf("  from_index: %d\n", best_position.from_index);
	printf("  to_index: %d\n", best_position.to_index);
	printf("best_score: %d\n", best_score);
	return (best_position);
}