/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:49:22 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 20:50:03 by ptison           ###   ########.fr       */
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

bool	get_better_position(t_position a, t_position b)
{
	return (better_position(a, b));
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
	int			rot;
	int			ib;
	int			ia;
	int			x;
	int			heuristic_estimate;
	int			total_score;

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
	best_score = INT_MAX;
	i = 0;
	while (i < count)
	{
		temp_size_a = arena->snapshot_arena->size_a;
		temp_size_b = arena->snapshot_arena->size_b;
		temp_a_values = malloc((temp_size_a + 1) * sizeof(int));
		temp_b_values = malloc((temp_size_b + 1) * sizeof(int));
		if (!temp_a_values || !temp_b_values)
		{
			if (temp_a_values)
				free(temp_a_values);
			if (temp_b_values)
				free(temp_b_values);
			best_position.total = INT_MAX;
			return (best_position);
		}
		memcpy(temp_a_values, arena->snapshot_arena->a_values, temp_size_a
			* sizeof(int));
		memcpy(temp_b_values, arena->snapshot_arena->b_values, temp_size_b
			* sizeof(int));
		position = candidates[i].position;
		rot = merged_cost(position.cost_a, position.cost_b);
		ib = normalize_index(temp_size_b, position.cost_b);
		ia = normalize_index(temp_size_a, position.cost_a);
		x = temp_b_values[ib];
		remove_element_at_index(temp_b_values, &temp_size_b, ib);
		insert_element_at_index(temp_a_values, &temp_size_a, ia, x);
		rot = rot + 1;
		heuristic_estimate = get_estimatation(temp_a_values, temp_size_a,
				arena->config.size_penalty_factor,
				arena->config.heuristic_offset,
				arena->config.heuristic_divisor);
		total_score = heuristic_estimate + rot;
		if (total_score < best_score || (total_score == best_score
				&& get_better_position(position, best_position)))
		{
			best_position = position;
			best_score = total_score;
		}
		free(temp_a_values);
		free(temp_b_values);
		i++;
	}
	return (best_position);
}
