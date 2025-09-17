/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:49:22 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 18:50:35 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/selector.h"
#include <stdbool.h>
#include <string.h>

static void	remove_element_at_index(int *array, int *size, int index)
{
	int	i;

	if (index < 0 || index >= *size)
		return ;
	i = index;
	while (i < *size - 1)
	{
		array[i] = array[i + 1];
		i++;
	}
	(*size)--;
}

static void	insert_element_at_index(int *array, int *size, int index, int value)
{
	int	i;

	if (index < 0 || index > *size)
		return ;
	if (*size >= 1000)
		return ;
	i = *size;
	while (i > index)
	{
		array[i] = array[i - 1];
		i--;
	}
	array[index] = value;
	(*size)++;
}

int	get_break_points(int *a, int size)
{
	int	n;
	int	breakpoints;

	if (size <= 1)
	{
		return (0);
	}
	n = size;
	breakpoints = 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (a[i] > a[i + 1])
		{
			breakpoints++;
		}
	}
	if (a[n - 1] > a[0])
	{
		breakpoints++;
	}
	return (breakpoints);
}

int	get_estimatation(int *temp_a, int size, int size_penalty_factor,
		int heuristic_offset, int heuristic_divisor)
{
	int	breakpoints;
	int	len;
	int	size_penalty;
	int	estimation;

	breakpoints = get_break_points(temp_a, size);
	len = size;
	size_penalty = len / size_penalty_factor;
	estimation = (breakpoints + size_penalty + heuristic_offset)
		/ heuristic_divisor;
	return (estimation);
}

static t_position	validate_lookahead_input(t_candidate *candidates,
		t_selector_arena *arena)
{
	t_position	invalid_position;

	invalid_position.total = INT_MAX;
	if (!arena || !arena->snapshot_arena || !candidates)
		return (invalid_position);
	if (arena->top_k_count == 0)
		return (invalid_position);
	return (candidates[0].position);
}

static void	copy_snapshot_to_temp(t_selector_arena *arena,
		int **temp_a_values, int **temp_b_values,
		int *temp_size_a, int *temp_size_b)
{
	*temp_size_a = arena->snapshot_arena->size_a;
	*temp_size_b = arena->snapshot_arena->size_b;
	*temp_a_values = arena->temp_a_values;
	*temp_b_values = arena->temp_b_values;
	memcpy(*temp_a_values, arena->snapshot_arena->a_values,
		*temp_size_a * sizeof(int));
	memcpy(*temp_b_values, arena->snapshot_arena->b_values,
		*temp_size_b * sizeof(int));
}

static int	simulate_move_operation(t_position position, int *temp_a_values,
		int *temp_b_values, int *temp_size_a, int *temp_size_b)
{
	int	rot;
	int	ib;
	int	ia;
	int	x;

	rot = merged_cost(position.cost_a, position.cost_b);
	ib = normalize_index(*temp_size_b, position.cost_b);
	ia = normalize_index(*temp_size_a, position.cost_a);
	x = temp_b_values[ib];
	remove_element_at_index(temp_b_values, temp_size_b, ib);
	insert_element_at_index(temp_a_values, temp_size_a, ia, x);
	return (rot + 1);
}

static int	calculate_candidate_score(t_position position __attribute__((unused)), int *temp_a_values,
		int temp_size_a, t_selector_arena *arena, int rotation_cost)
{
	int	heuristic_estimate;

	heuristic_estimate = get_estimatation(temp_a_values, temp_size_a,
			arena->config.size_penalty_factor,
			arena->config.heuristic_offset,
			arena->config.heuristic_divisor);
	return (heuristic_estimate + rotation_cost);
}

static bool	update_best_if_better(t_position *best_position, int *best_score,
		t_position current_position, int current_score)
{
	if (current_score < *best_score || (current_score == *best_score
			&& is_better_position(current_position, *best_position)))
	{
		*best_position = current_position;
		*best_score = current_score;
		return (true);
	}
	return (false);
}

t_position	evaluate_with_lookahead(t_candidate *candidates,
		t_selector_arena *arena)
{
	t_position	best_position;
	int			i;
	int			count;
	int			*temp_a_values;
	int			*temp_b_values;
	int			temp_size_a;
	int			temp_size_b;
	int			best_score;
	t_position	position;
	int			rotation_cost;
	int			total_score;

	best_position = validate_lookahead_input(candidates, arena);
	if (best_position.total == INT_MAX)
		return (best_position);
	count = arena->top_k_count;
	best_score = INT_MAX;
	i = 0;
	while (i < count)
	{
		copy_snapshot_to_temp(arena, &temp_a_values, &temp_b_values,
			&temp_size_a, &temp_size_b);
		position = candidates[i].position;
		rotation_cost = simulate_move_operation(position, temp_a_values,
				temp_b_values, &temp_size_a, &temp_size_b);
		total_score = calculate_candidate_score(position, temp_a_values,
				temp_size_a, arena, rotation_cost);
		update_best_if_better(&best_position, &best_score, position,
			total_score);
		i++;
	}
	return (best_position);
}
