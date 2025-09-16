/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:42 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 22:04:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECTOR_H
# define SELECTOR_H

# include "../libft/include/libft.h"
# include "ops.h"
# include "simulation_config.h"
# include "snapshot_arena.h"
# include "stack.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_position
{
	int					total;
	int					cost_a;
	int					cost_b;
	int					from_index;
	int					to_index;
}						t_position;

typedef struct s_candidate
{
	t_position			position;
	int					score;
}						t_candidate;

typedef enum e_move_direction
{
	MOVE_A_TO_B = 0,
	MOVE_B_TO_A
}						t_move_direction;

typedef struct s_selector_arena
{
	t_simulation_config	config;
	t_candidate			*candidates;
	int					candidate_count;
	t_snapshot_arena	*snapshot_arena;
	t_candidate			*filtered_candidates;
	int					filtered_count;
	t_candidate			*top_k_candidates;
	int					top_k_count;
	void				*arena_memory;
	size_t				arena_size;
	int					max_candidates;
}						t_selector_arena;

t_selector_arena		*allocate_selector_arena(int max_candidates);
void					free_selector_arena(t_selector_arena *arena);

t_position				execute_selection_algorithm(t_sorting_state *state,
							t_move_direction direction,
							t_selector_arena *arena);
t_candidate				*build_filtered_candidates(t_candidate *candidates,
							int threshold_offset, t_selector_arena *arena);
t_candidate				*build_top_k_candidates(t_candidate *candidates,
							int max_k, t_selector_arena *arena);
t_position				build_best_position(t_candidate *candidates);
bool					is_better_position(t_position a, t_position b);
int						find_insertion_index(int *sorted_array, int array_size,
							int target_value);
int						find_target_position(int *sorted_array, int array_size,
							int target_value);
int						normalize_index(int array_size, int raw_index);
int						merged_cost(int a, int b);
int						signed_cost(int idx, int size);
int						get_max_stack_size(t_stack *a, t_stack *b);

t_candidate				*enumerate_candidates(t_sorting_state *state,
							t_selector_arena *arena);

t_position				evaluate_with_lookahead(t_candidate *candidates,
							t_selector_arena *arena);

t_position				select_best_move(t_sorting_state *ps,
							int max_candidates, t_simulation_config config);
t_candidate				*enumerate_b_to_a_candidates(t_sorting_state *state,
							t_selector_arena *arena);
#endif
