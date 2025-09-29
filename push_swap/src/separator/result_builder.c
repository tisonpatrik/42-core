/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:52:53 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 21:52:54 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

/*
 * Reconstructs the LIS sequence from tracking arrays.
 * 1. Start from the best ending position
 * 2. Follow the previous_indices chain backwards
 * 3. Collect all nodes in the LIS
 * 4. The sequence is built backwards, so it needs to be reversed
 *
 * @param lis_nodes: Array to store the reconstructed LIS nodes
 * @param computation: The LIS computation state with tracking arrays
 * @param computation_result: The result containing best length and end position
 */
static void	create_lis_sequence_from_tracking(t_node **lis_nodes,
		t_lis_computation *computation, t_lis_result *computation_result)
{
	size_t	result_index;
	int		current_index;

	result_index = 0;
	current_index = computation_result->best_end;
	while (current_index != -1
		&& result_index < (size_t)computation_result->best_len)
	{
		lis_nodes[result_index] = computation->nodes[current_index];
		result_index++;
		current_index = computation->previous_indices[current_index];
	}
}

/*
 * Reverses the LIS sequence to get the correct increasing order.
 *
 * The reconstruction builds the sequence backwards (from end to start),
 * so we reverse it to get the natural increasing order.
 *
 * @param lis_nodes: Array of LIS nodes to reverse
 * @param lis_count: Number of nodes in the LIS
 */
static void	reverse_sequence_to_correct_order(t_node **lis_nodes,
		size_t lis_count)
{
	size_t	swap_index;
	t_node	*temporary_node;

	swap_index = 0;
	while (swap_index < lis_count / 2)
	{
		temporary_node = lis_nodes[swap_index];
		lis_nodes[swap_index] = lis_nodes[lis_count - 1 - swap_index];
		lis_nodes[lis_count - 1 - swap_index] = temporary_node;
		swap_index++;
	}
	lis_nodes[lis_count] = NULL;
}

/*
 * Builds the final LIS result by reconstructing and ordering the sequence.
 *
 * This function orchestrates the reconstruction process:
 * 1. Reconstructs the LIS sequence from tracking arrays
 * 2. Reverses the sequence to get correct increasing order
 * 3. Returns the properly ordered array of LIS nodes
 *
 * @param computation: The LIS computation state
 * @param computation_result: The computed LIS result
 * @param arena: Memory arena containing the lis_nodes array
 * @return: Array of nodes forming the longest increasing subsequence
 */
void	build_lis_result(t_lis_computation *computation,
		t_lis_result *computation_result, t_separator_arena *arena)
{
	create_lis_sequence_from_tracking(arena->lis_nodes, computation,
		computation_result);
	reverse_sequence_to_correct_order(arena->lis_nodes,
		computation_result->best_len);
}
