/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:28 by patrik            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATOR_H
# define SEPARATOR_H

# include "ops.h"
# include "stack.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_lis_result
{
	int					best_len;
	int					best_end;
}						t_lis_result;

typedef struct s_lis_computation
{
	int					n;
	t_node				**nodes;
	int					*values;
	int					*lis_lengths;
	int					*previous_indices;
}						t_lis_computation;

typedef struct s_separator_arena
{
	t_lis_computation	*computation;
	t_node				**lis_nodes;
	void				*arena_memory;
	size_t				arena_size;
}						t_separator_arena;

void					push_non_lis_into_b(t_sorting_state *state);
t_separator_arena		*allocate_separator_arena(int element_count);
void					free_separator_arena(t_separator_arena *arena);
t_node					**execute_lis_algorithm(t_stack *stack,
							t_separator_arena *arena);
t_node					**get_lis_nodes(t_stack *stack,
							t_separator_arena *arena);

t_node					**build_lis_result(t_lis_computation *computation,
							t_lis_result *computation_result,
							t_separator_arena *arena);
void					compute_longest_increasing_lengths(t_lis_computation *computation,
							t_lis_result *best_result);
int						extract_stack_values_to_computation(t_stack *stack,
							t_lis_computation *computation);
#endif
