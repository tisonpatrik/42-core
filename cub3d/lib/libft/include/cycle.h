/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:36:56 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:36:56 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYCLE_H
# define CYCLE_H

# include <stddef.h>

typedef struct s_step_cycle
{
	double	accumulator;
	size_t	index;
}	t_step_cycle;

t_step_cycle	ft_step_cycle_create(void);
void			ft_step_cycle_advance(t_step_cycle *cycle, double delta_time,
					double interval, size_t count);

#endif
