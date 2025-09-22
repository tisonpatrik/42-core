/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:50:33 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:27:46 by ptison           ###   ########.fr       */
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
	int			len_of_inputs;
}				t_sorting_state;

t_sorting_state	*create_sorting_state(int *numbers, int n);
t_sorting_state	*create_state_for_checker(int *numbers, int n,
					t_list *operations);
void			free_sorting_state(t_sorting_state *state);
void			save_operation(t_sorting_state *state, t_operation operation);
void			print_operation(t_operation op);
void			print_operations(t_sorting_state *state);

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
