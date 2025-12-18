/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:57:30 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:59:45 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

void	do_sleeping(t_philosopher *philo)
{
	write_status(philo, "is sleeping");
	precise_sleep(philo->table, philo->table->time_to_sleep);
}

void	do_thinking(t_philosopher *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	write_status(philo, "is thinking");
	if (philo->table->nb_philos % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_sleep(philo->table, t_think * 0.4);
}
