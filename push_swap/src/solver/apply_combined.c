/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_combined.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:10:24 by ptison            #+#    #+#             */
/*   Updated: 2025/09/17 21:22:39 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/solver.h"

static void	apply_combined_rotations(t_sorting_state *ps, int *a, int *b)
{
	while (*a > 0 && *b > 0)
	{
		rotate_ab(ps);
		(*a)--;
		(*b)--;
	}
	while (*a < 0 && *b < 0)
	{
		reverse_rotate_ab(ps);
		(*a)++;
		(*b)++;
	}
}

static void	apply_individual_rotations(t_sorting_state *ps, int *a, int *b)
{
	while (*a > 0)
	{
		rotate_a(ps);
		(*a)--;
	}
	while (*a < 0)
	{
		reverse_rotate_a(ps);
		(*a)++;
	}
	while (*b > 0)
	{
		rotate_b(ps);
		(*b)--;
	}
	while (*b < 0)
	{
		reverse_rotate_b(ps);
		(*b)++;
	}
}

void	apply_combined(t_sorting_state *ps, t_position p, bool push_to_b)
{
	int	a;
	int	b;

	a = p.cost_a;
	b = p.cost_b;
	apply_combined_rotations(ps, &a, &b);
	apply_individual_rotations(ps, &a, &b);
	if (push_to_b)
		push_b(ps);
	else
		push_a(ps);
}
