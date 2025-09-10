/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:42 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:37:49 by patrik           ###   ########.fr       */
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

typedef struct s_selector_config
{
	int	max_candidates;
	int	cost_threshold_offset;
	int	size_penalty_factor;
	int	heuristic_offset;
	int	heuristic_divisor;
}	t_selector_config;

typedef struct s_cost_calculator
{
	t_selector_config	config;
}	t_cost_calculator;

typedef struct s_candidate_enumerator
{
	t_cost_calculator	*cost_calc;
	t_selector_config	config;
}	t_candidate_enumerator;

typedef struct s_move_simulator
{
}	t_move_simulator;

typedef struct s_lookahead_evaluator
{
	t_selector_config	config;
	t_move_simulator	*simulator;
}	t_lookahead_evaluator;

t_selector_config	default_selector_config(void);

t_cost_calculator	*new_cost_calculator(t_selector_config config);
void				free_cost_calculator(t_cost_calculator *calc);
t_position			calculate_position_cost(t_cost_calculator *calc,
						int from_idx, int to_idx, int size_a, int size_b);
int					calculate_penalty(t_cost_calculator *calc, int *stack,
						int size, int to_idx, int val);
int					calculate_merged_cost(t_cost_calculator *calc,
						int cost_a, int cost_b);

t_candidate_enumerator	*new_candidate_enumerator(t_selector_config config);
void					free_candidate_enumerator(
							t_candidate_enumerator *enumerator);
t_candidate			*enumerate_a_to_b(t_candidate_enumerator *enumerator,
						t_stack *a, t_stack *b, int *count);
t_candidate			*enumerate_b_to_a(t_candidate_enumerator *enumerator,
						int *a, int size_a, int *b, int size_b, int *count);
t_candidate			*build_candidates_from_stack_a(
						t_candidate_enumerator *enumerator,
						t_stack *a, t_stack *b, int *count);

t_move_simulator	*new_move_simulator(void);
void				free_move_simulator(t_move_simulator *simulator);
int					simulate_move(t_move_simulator *simulator, t_stack *stack_a,
						t_stack *stack_b, t_position position,
						t_move_direction direction, t_stack **new_stack_a, t_stack **new_stack_b);

t_lookahead_evaluator	*new_lookahead_evaluator(t_selector_config config);
void					free_lookahead_evaluator(
							t_lookahead_evaluator *evaluator);
t_position				evaluate_with_lookahead(
							t_lookahead_evaluator *evaluator,
							t_stack *stack_a, t_stack *stack_b,
							t_candidate *candidates, int count,
							t_move_direction direction);
int						calculate_heuristic(t_lookahead_evaluator *evaluator,
							t_stack *stack);

bool				better_position(t_position a, t_position b);

t_candidate		new_candidate(t_position pos, int score);
t_candidate		*filter_candidates_by_threshold(t_candidate *candidates,
					int count, int threshold_offset, int *filtered_count);
t_candidate		*select_top_k_candidates(t_candidate *candidates,
					int count, int max_k, int *result_count);
t_position		select_best_candidate(t_candidate *candidates, int count);

int				merged_cost(int a, int b);
int				signed_cost(int idx, int size);

bool			is_empty(int *arr, int size);
bool			is_empty_or_single(int *arr, int size);

int				*remove_element_at(int *arr, int size, int index,
					int *new_size);
int				*insert_element_at(int *arr, int size, int index,
					int value, int *new_size);
int				*snapshot_stack(t_stack *stack, int *size);
int				calculate_breakpoints(int *arr, int size);

int				binary_search_insertion_point(int *arr, int size, int val,
					bool (*comparator)(int, int));
int				find_insertion_index(int *sorted_arr, int size, int val);
int				find_target_position(int *sorted_arr, int size, int val);
int				normalize_index(int n, int k);

t_position		select_best_a_to_b_move(t_sorting_state *ps);
t_position		cheapest_a_to_b(t_sorting_state *ps);
t_position		select_best_b_to_a_move(t_sorting_state *ps,
					int max_candidates);
t_position		pick_near_best(t_sorting_state *ps, int max_candidates);

t_position		select_best_candidate_with_lookahead(t_stack *stack_a,
					t_stack *stack_b, t_candidate *candidates, int count,
					int max_candidates, t_selector_config config,
					t_move_direction direction);

int				ft_abs(int n);

#endif