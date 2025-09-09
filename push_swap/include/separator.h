/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:28 by patrik            #+#    #+#             */
/*   Updated: 2025/09/09 20:40:33 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATOR_H
# define SEPARATOR_H

#include <stdbool.h>
#include "stack.h"
#include <stddef.h>
#include "ops.h"

/**
 * Represents a node with an associated boolean flag.
 * Used in LIS results to mark which nodes are part of the sequence.
 */
typedef struct s_tnode_bool {
    t_node* node;   
    bool    value;  
} t_node_bool;

/**
 * Array of node-boolean pairs representing LIS results.
 */
typedef struct s_node_bool_array {
    t_node_bool* items;  
    size_t       count;  
} t_node_bool_array;

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
typedef struct s_lis_computation_data
{
	int	*vals;  
	int	n;     
	int	*lis;  
	int	*prev; 
}	t_lis_computation_data;

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

t_node_bool_array* get_lis_nodes(t_stack *stack);
t_node_bool_array* get_lis_nodes_impl(t_stack *stack, int n);
void	compute_longest_increasing_lengths(t_lis_computation_data *data,
		t_lis_result *result);
t_node_bool_array* build_lis_result_from_computation(t_lis_arrays *arrays,
		t_lis_result *lis_result);
void	reconstruct_lis_sequence_from_tracking(t_node_bool_array *result,
		t_lis_arrays *arrays, t_lis_result *lis_result);
void	reverse_sequence_to_correct_order(t_node_bool_array *result);
void push_non_lis_into_b(t_sorting_state *state);

#endif
