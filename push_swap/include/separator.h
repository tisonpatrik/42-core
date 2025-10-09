/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:28:01 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 11:34:52 by ptison           ###   ########.fr       */
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
	size_t				lis_length;
	t_arena				*arena;
}						t_separator_arena;

void					push_non_lis_into_b(t_sorting_state *state);
t_separator_arena		*allocate_separator_arena(int element_count);
void					free_separator_arena(t_separator_arena *arena);

void					get_lis_nodes(t_stack *stack, t_separator_arena *arena);

void					build_lis_result(t_lis_computation *computation,
							t_lis_result *computation_result,
							t_separator_arena *arena);
void					process_stack_elements(t_sorting_state *state,
							int size_a, t_node **lis_nodes);
void					compute_longest_lens(t_lis_computation *computation,
							t_lis_result *best_result);
void					reverse_chain_mode(t_sorting_state *state);
int						get_count_of_breaks(t_stack *a, int size);
#endif
