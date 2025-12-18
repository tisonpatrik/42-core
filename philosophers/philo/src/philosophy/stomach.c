/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stomach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:56:42 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:56:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophy.h"
#include "../../include/simulation.h"

static void	update_meal_stats(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
}

static void	increment_meal_counter(t_philosopher *philo)
{
	if (has_simulation_stopped(philo->table))
		return ;
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->times_ate += 1;
	pthread_mutex_unlock(&philo->meal_time_lock);
}

void	do_eating(t_philosopher *philo)
{
	take_forks(philo);
	write_status(philo, "is eating");
	update_meal_stats(philo);
	precise_sleep(philo->table, philo->table->time_to_eat);
	increment_meal_counter(philo);
	drop_forks(philo);
}
