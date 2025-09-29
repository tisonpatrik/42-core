/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:56 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 22:17:17 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECTOR_H
# define SELECTOR_H

# include "../libft/include/libft.h"
# include "ops.h"
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
	bool				is_valid;
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

typedef struct s_simulation_config
{
	int					max_candidates;
	int					cost_threshold_offset;
	int					size_penalty_factor;
	int					heuristic_offset;
	int					heuristic_divisor;
}						t_simulation_config;

t_simulation_config		default_selector_config(void);

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
	t_arena				*arena;
	int					max_candidates;
	int					*temp_a_values;
	int					*temp_b_values;
}						t_selector_arena;

t_selector_arena		*allocate_arena(int max_candidates, int len_of_inputs);
void					free_selector_arena(t_selector_arena *arena);

bool					build_filtered_candidates(t_candidate *candidates,
							int threshold_offset, t_selector_arena *arena);
bool					build_top_k_candidates(t_candidate *candidates,
							int max_k, t_selector_arena *arena);
bool					is_better_position(t_position a, t_position b);

int						find_target_position(int *sorted_array, int array_size,
							int target_value);
int						merged_cost(int a, int b);
int						signed_cost(int idx, int size);

bool					enumerate_candidates(t_sorting_state *state,
							t_selector_arena *arena);

t_position				evaluate_with_lookahead(t_candidate *candidates,
							t_selector_arena *arena);

t_position				select_best_move(t_sorting_state *ps);

int						compare_candidates(t_candidate *a, t_candidate *b);
t_position				create_invalid_position(void);
#endif
