/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fallback_strategy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:54:04 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 11:44:54 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

static void	rotate_min_to_top_upwards(t_sorting_state *state, int min_index_a)
{
	int	rotation_steps;

	rotation_steps = 0;
	while (rotation_steps < min_index_a)
	{
		rotate_a(state);
		rotation_steps++;
	}
}

static void	rotate_min_to_top_downwards(t_sorting_state *state, int min_index_a,
		int total_size_a)
{
	while (min_index_a < total_size_a)
	{
		reverse_rotate_a(state);
		min_index_a++;
	}
}

/*
 * Implements "reverse chain mode" as a fallback when the LIS is too short.
 * In this mode, we only perform separation:
 *  - Keep the smallest element in stack A
 *  - Push all other elements to stack B
 *
 * The standard reinsertion phase will later merge stack B back into A.
 */
void	reverse_chain_mode(t_sorting_state *state)
{
	int	total_size_a;
	int	min_index_a;

	total_size_a = get_size(state->a);
	if (total_size_a <= 1)
		return ;
	min_index_a = find_min_index(state->a);
	if (min_index_a <= total_size_a / 2)
	{
		rotate_min_to_top_upwards(state, min_index_a);
	}
	else
	{
		rotate_min_to_top_downwards(state, min_index_a, total_size_a);
	}
	while (get_size(state->a) > 1)
		push_b(state);
}
