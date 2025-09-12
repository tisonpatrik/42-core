/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:28 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 03:10:52 by patrik           ###   ########.fr       */
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
 * Data structure for LIS dynamic programming computation.
 */
typedef struct s_lis_comp_data
{
	int	*vals;
	int	n;
	int	*lis;
	int	*prev;
}	t_lis_comp_data;

/**
 * Parameters for memory allocation during LIS computation.
 */
typedef struct s_allocation_data
{
	int				n;
	t_node			***nodes;
	int				**vals;
	int				**lis;
	int				**prev;
}	t_allocation_data;

/**
 * Collection of all arrays used during LIS computation.
 */
typedef struct s_lis_arrays
{
	t_node			**nodes;
	int				*vals;
	int				*lis;
	int				*prev;
}	t_lis_arrays;

t_node_bool_array	*allocate_lis_memory(t_allocation_data *allocation_data);
t_node_bool_array	*execute_lis_algorithm(t_stack *stack, int element_count);
t_node_bool_array	*get_lis_nodes(t_stack *stack);
int	extract_stack_values_to_arrays(t_stack *stack, t_node **nodes, int *values,
		int count);
t_node_bool_array	*build_lis_result(t_lis_arrays *algorithm_data,
		t_lis_result *computation_result);
void	free_lis_computation_memory(t_node **nodes, int *values,
		int *subsequence_lengths, int *previous_indices);
#endif
