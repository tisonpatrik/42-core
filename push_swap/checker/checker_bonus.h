/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:26 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "../../libft/include/libft.h"
# include "../include/ops.h"
# include "../include/validator.h"

typedef struct s_checker_state
{
	t_stack		*a;
	t_stack		*b;
	t_list		*operations;
	int			len_of_inputs;
}				t_checker_state;

t_list			*get_operations(void);
t_operation		parse_operation_string(const char *str);
t_checker_state	*create_state_for_checker(int *input, int count,
					t_list *operations);
void			check_result(t_checker_state *state);
void			free_checker_state(t_checker_state *state);
bool			apply_swap_operation(t_checker_state *state, t_operation op);
bool			apply_push_operation(t_checker_state *state, t_operation op);
bool			apply_rotate_operation(t_checker_state *state, t_operation op);
bool			apply_reverse_rotate_operation(t_checker_state *state,
					t_operation op);

#endif
