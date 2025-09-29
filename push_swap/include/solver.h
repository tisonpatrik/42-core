/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:15:15 by ptison            #+#    #+#             */
/*   Updated: 2025/09/28 15:50:12 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# include "ops.h"
# include "selector.h"
# include "stack.h"
# include "validator.h"
# include <stdlib.h>
# include <unistd.h>

void	solve_push_swap(t_sorting_state *state);
void	apply_combined(t_sorting_state *ps, t_position p, bool push_to_b);
void	align_min_to_top(t_sorting_state *ps);
void	sort_three(t_sorting_state *ps);

#endif
