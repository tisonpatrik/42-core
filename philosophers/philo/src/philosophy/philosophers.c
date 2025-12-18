/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:57:17 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:57:21 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

static void	*handle_single_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
	write_status(philo, "has taken a fork");
	precise_sleep(philo->table, philo->table->time_to_die);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_left]);
	return (NULL);
}

static void	wait_for_simulation_start(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
}

static void	desynchronize_philosophers(t_philosopher *philo)
{
	if (philo->table->nb_philos % 2 == 0)
	{
		if (philo->id % 2)
			precise_sleep(philo->table, 20);
	}
	else
	{
		if (philo->id % 2)
			do_thinking(philo);
	}
}

void	*do_philosophy(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	wait_for_simulation_start(philo);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (handle_single_philosopher(philo));
	desynchronize_philosophers(philo);
	while (!has_simulation_stopped(philo->table))
	{
		do_eating(philo);
		do_sleeping(philo);
		do_thinking(philo);
	}
	return (NULL);
}
