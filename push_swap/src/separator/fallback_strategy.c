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
