/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:28 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 19:17:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATOR_H
# define SEPARATOR_H

# include <stdbool.h>
# include "stack.h"
# include <stddef.h>
# include "ops.h"

/**
 * Represents a node with an associated boolean flag.
 * Used in LIS results to mark which nodes are part of the sequence.
 */
typedef struct s_tnode_bool
{
	t_node	*node;
	bool	value;
}	t_node_bool;

/**
 * Array of node-boolean pairs representing LIS results.
 */
typedef struct s_node_bool_array
{
	t_node_bool	*items;
	size_t		count;
}	t_node_bool_array;

/**
 * Result of LIS computation containing the best sequence found.
 */
typedef struct s_lis_result
{
	int	best_len;
	int	best_end;
}	t_lis_result;

/**
 * Unified structure for LIS computation containing all necessary data.
 */
typedef struct s_lis_computation
{
	int				n;					// Number of elements
	t_node			**nodes;			// Pointers to stack nodes
	int				*values;			// Node values
	int				*lis_lengths;		// LIS lengths for each position
	int				*previous_indices;	// Previous indices for reconstruction
}	t_lis_computation;

void	push_non_lis_into_b(t_sorting_state *state);
t_lis_computation	*allocate_lis_arena(int element_count);
void	free_lis_arena(t_lis_computation *computation);
t_node_bool_array	*execute_lis_algorithm(t_stack *stack, int element_count);
t_node_bool_array	*get_lis_nodes(t_stack *stack);

t_node_bool_array	*build_lis_result(t_lis_computation *computation,
		t_lis_result *computation_result);
void	compute_longest_increasing_lengths(t_lis_computation *computation,
		t_lis_result *best_result);
int	extract_stack_values_to_computation(t_stack *stack, t_lis_computation *computation);
#endif
