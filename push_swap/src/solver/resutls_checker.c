/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resutls_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:07:40 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/solver.h"

void validate_inputs(t_sorting_state *state)
{
    if (state->a->size == 0)
    {
        exit(1);
    }
    if (is_sorted(state->a))
    {
        ft_printf("OK\n");
        exit(1);
    }
}


void	check_result(t_sorting_state *state)
{
	if (is_sorted(state->a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}