/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by patrik            #+#    #+#             */
/*   Updated: 2025/09/15 21:37:10 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <string.h>



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
	// Safety check: don't increase size beyond reasonable bounds
	if (*size >= 1000) // Arbitrary safety limit
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

t_position	evaluate_with_lookahead(t_candidate *candidates, t_selector_arena *arena, t_move_direction direction)
{
	t_position	best_position;
	int			i;
	int			count;
	int			*temp_a_values;
	int			*temp_b_values;
	int			temp_size_a;
	int			temp_size_b;

	if (!arena || !arena->snapshot_arena || !candidates)
	{
		best_position.total = INT_MAX;
		return (best_position);
	}

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
		// Create temporary working copies for this evaluation
		temp_size_a = arena->snapshot_arena->size_a;
		temp_size_b = arena->snapshot_arena->size_b;
		
		// Allocate temporary arrays with extra space for modifications
		// We need extra space because insert_element_at_index can increase size
		temp_a_values = malloc((temp_size_a + 1) * sizeof(int));
		temp_b_values = malloc((temp_size_b + 1) * sizeof(int));
		
		if (!temp_a_values || !temp_b_values)
		{
			if (temp_a_values) free(temp_a_values);
			if (temp_b_values) free(temp_b_values);
			best_position.total = INT_MAX;
			return (best_position);
		}
		
		// Copy original values
		memcpy(temp_a_values, arena->snapshot_arena->a_values, temp_size_a * sizeof(int));
		memcpy(temp_b_values, arena->snapshot_arena->b_values, temp_size_b * sizeof(int));
		
		t_position	position = candidates[i].position;
		int			rot = merged_cost(position.cost_a, position.cost_b);
		
	
		if (direction == MOVE_A_TO_B)
		{
			int	ia = normalize_index(temp_size_a, position.cost_a);
			int	ib = normalize_index(temp_size_b, position.cost_b);
			int	x = temp_a_values[ia];
			
			remove_element_at_index(temp_a_values, &temp_size_a, ia);
			insert_element_at_index(temp_b_values, &temp_size_b, ib, x);
			rot = rot + 1;
		}
		else
		{
			int	ib = normalize_index(temp_size_b, position.cost_b);
			int	ia = normalize_index(temp_size_a, position.cost_a);
			int	x = temp_b_values[ib];
			
			remove_element_at_index(temp_b_values, &temp_size_b, ib);
			insert_element_at_index(temp_a_values, &temp_size_a, ia, x);
			rot = rot + 1;
		}

		int heuristic_estimate = get_estimatation(temp_a_values, temp_size_a, arena->config.size_penalty_factor, arena->config.heuristic_offset, arena->config.heuristic_divisor);
		int total_score = heuristic_estimate + rot;
		
		
		if (total_score < best_score || (total_score == best_score && get_better_position(position, best_position)))
		{
			best_position = position;
			best_score = total_score;
		}

		// Clean up temporary arrays
		free(temp_a_values);
		free(temp_b_values);
		
		i++;
	}

		return (best_position);
}