/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:26 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:27:27 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHECKER_H
# define CHECKER_H

# include "../../libft/include/libft.h"
# include "../include/ops.h"
# include "../include/validator.h"

t_list			*get_operations(void);
t_operation		parse_operation_string(const char *str);
t_sorting_state	*create_state_for_checker(int *input, int count, t_list *operations);
void			check_result(t_sorting_state *state);
void			free_sorting_state(t_sorting_state *state);

#endif
