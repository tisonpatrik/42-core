/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:42 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 00:32:27 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECTOR_H
# define SELECTOR_H

# include "../libft/include/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include "stack.h"
# include "ops.h"
# include "simulation_config.h"
# include "snapshot_arena.h"

typedef struct s_position
{
	int		total;
	int		cost_a;
	int		cost_b;
	int		from_index;
	int		to_index;
}	t_position;

typedef struct s_candidate
{
	t_position	position;
	int			score;
}	t_candidate;

typedef enum e_move_direction
{
	MOVE_A_TO_B = 0,
	MOVE_B_TO_A
}	t_move_direction;



/**
 * Unified arena structure for selector operations containing all memory allocations.
 */
typedef struct s_selector_arena
{
	t_simulation_config	config;					// Configuration parameters
	t_candidate			*candidates;			// Array of candidates
	int					candidate_count;		// Number of candidates generated
	t_snapshot_arena	*snapshot_arena;		// Snapshot arena
	t_candidate			*filtered_candidates;	// Array of filtered candidates
	int					filtered_count;			// Number of filtered candidates
	t_candidate			*top_k_candidates;		// Array of top-k candidates
	int					top_k_count;			// Number of top-k candidates
	void				*arena_memory;			// Single memory block for all allocations
	size_t				arena_size;				// Total size of allocated memory
	int					max_candidates;			// Maximum number of candidates
}	t_selector_arena;

// Arena management
t_selector_arena	*allocate_selector_arena(int max_candidates);
void				free_selector_arena(t_selector_arena *arena);

// Algorithm execution
t_position			execute_selection_algorithm(t_sorting_state *state, 
						t_move_direction direction, t_selector_arena *arena);
// Result building
t_candidate			*build_filtered_candidates(t_candidate *candidates,
						int threshold_offset, t_selector_arena *arena);
t_candidate			*build_top_k_candidates(t_candidate *candidates,
						int max_k, t_selector_arena *arena);
t_position			build_best_position(t_candidate *candidates);

// Core utilities
bool				better_position(t_position a, t_position b);
int					find_insertion_index(int *sorted_array, int array_size, int target_value);
int					find_target_position(int *sorted_array, int array_size, int target_value);
int					normalize_index(int array_size, int raw_index);
int					merged_cost(int a, int b);
int					signed_cost(int idx, int size);
int					get_max_stack_size(t_stack *a, t_stack *b);

// Candidate enumeration
t_candidate			*enumerate_candidates(t_sorting_state *state, t_selector_arena *arena);

// Lookahead evaluation
t_position			evaluate_with_lookahead(t_candidate *candidates, t_selector_arena *arena);

// Legacy interface (to be updated)
t_position			select_best_b_to_a_move(t_sorting_state *ps, int max_candidates, t_simulation_config config);
t_candidate	*enumerate_b_to_a_candidates(t_sorting_state *state, t_selector_arena *arena);
#endif