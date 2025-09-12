/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:28 by patrik            #+#    #+#             */
/*   Updated: 2025/09/12 20:01:46 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATOR_H
# define SEPARATOR_H

# include <stdbool.h>
# include "stack.h"
# include <stddef.h>
# include "ops.h"

// No need for a separate struct - we'll return t_node** and size_t directly

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

/**
 * Unified arena structure for separator operations containing all memory allocations.
 */
typedef struct s_separator_arena
{
	t_lis_computation	*computation;		// LIS computation data
	t_node				**lis_nodes;		// Array of nodes in LIS
	void				*arena_memory;		// Single memory block for all allocations
	size_t				arena_size;			// Total size of allocated memory
}	t_separator_arena;

void	push_non_lis_into_b(t_sorting_state *state);
t_separator_arena	*allocate_separator_arena(int element_count);
void	free_separator_arena(t_separator_arena *arena);
t_node	**execute_lis_algorithm(t_stack *stack, t_separator_arena *arena);
t_node	**get_lis_nodes(t_stack *stack, t_separator_arena *arena);

t_node	**build_lis_result(t_lis_computation *computation,
		t_lis_result *computation_result, t_separator_arena *arena);
void	compute_longest_increasing_lengths(t_lis_computation *computation,
		t_lis_result *best_result);
int	extract_stack_values_to_computation(t_stack *stack, t_lis_computation *computation);
#endif
