
#ifndef SOLVER_H
# define SOLVER_H

# include "ops.h"
# include "selector.h"

void	solve_push_swap(t_sorting_state *state);
void	apply_combined(t_sorting_state *ps, t_position p, bool push_to_b);
void	align_min_to_top(t_sorting_state *ps);
void	sort_three(t_sorting_state *ps);

#endif