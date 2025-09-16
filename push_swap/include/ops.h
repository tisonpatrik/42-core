/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:50:33 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:40:58 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "../libft/include/libft.h"
# include "stack.h"

typedef enum e_operation
{
	SA = 0,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}				t_operation;

typedef struct s_sorting_state
{
	t_stack		*a;
	t_stack		*b;
	t_list		*operations;
}				t_sorting_state;

t_sorting_state	*create_sorting_state(int *numbers, int n);
void			free_sorting_state(t_sorting_state *state);
void			save_operation(t_sorting_state *state, t_operation operation);
void			print_operations(t_sorting_state *state);
void			print_operations_as_numbers(t_sorting_state *state);
void			print_state_values(t_sorting_state *state);

void			swap_a(t_sorting_state *state);
void			swap_b(t_sorting_state *state);
void			swap_ab(t_sorting_state *state);
void			push_a(t_sorting_state *state);
void			push_b(t_sorting_state *state);
void			rotate_a(t_sorting_state *state);
void			rotate_b(t_sorting_state *state);
void			rotate_ab(t_sorting_state *state);
void			reverse_rotate_a(t_sorting_state *state);
void			reverse_rotate_b(t_sorting_state *state);
void			reverse_rotate_ab(t_sorting_state *state);

#endif
