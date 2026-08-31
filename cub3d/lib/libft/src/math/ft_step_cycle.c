/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_step_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:41:23 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:41:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cycle.h"

t_step_cycle	ft_step_cycle_create(void)
{
	return ((t_step_cycle){0.0, 0});
}

void	ft_step_cycle_advance(t_step_cycle *cycle, double delta_time,
	double interval, size_t count)
{
	if (!cycle || delta_time <= 0.0 || interval <= 0.0 || count == 0)
		return ;
	cycle->accumulator += delta_time;
	while (cycle->accumulator >= interval)
	{
		cycle->accumulator -= interval;
		cycle->index = (cycle->index + 1) % count;
	}
}
