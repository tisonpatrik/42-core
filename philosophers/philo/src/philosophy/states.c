/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:56:53 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:56:57 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

void	write_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!has_simulation_stopped(philo->table))
	{
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
			philo->id + 1, status);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	precise_sleep(t_table *table, time_t duration)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + duration;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(table))
			break ;
		usleep(100);
	}
}
