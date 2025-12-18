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

static time_t	calculate_think_time(t_philosopher *philo)
{
	time_t	time_since_meal;
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_since_meal = get_time_in_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die - time_since_meal
			- philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 600)
		time_to_think = 200;
	return (time_to_think);
}

void	do_sleeping(t_philosopher *philo)
{
	write_status(philo, "is sleeping");
	precise_sleep(philo->table, philo->table->time_to_sleep);
}

void	do_thinking(t_philosopher *philo)
{
	time_t	think_time;

	write_status(philo, "is thinking");
	if (philo->table->nb_philos % 2 == 0)
		return ;
	think_time = calculate_think_time(philo);
	precise_sleep(philo->table, think_time);
}
