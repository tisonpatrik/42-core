/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:54:31 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 14:03:03 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

bool	has_simulation_stopped(t_table *table)
{
	bool	r;

	pthread_mutex_lock(&table->sim_stop_lock);
	r = table->sim_stop;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (r);
}

static void	set_sim_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

static bool	kill_philo(t_philosopher *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		pthread_mutex_lock(&philo->table->write_lock);
		printf("%ld %d died\n", time - philo->table->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_simulation *sim)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < sim->table.nb_philos)
	{
		pthread_mutex_lock(&sim->philos[i]->meal_time_lock);
		if (kill_philo(sim->philos[i]))
			return (true);
		if (sim->table.must_eat_count != -1)
		{
			if (sim->philos[i]->times_ate < (unsigned int)sim->table.must_eat_count)
				all_ate_enough = false;
		}
		pthread_mutex_unlock(&sim->philos[i]->meal_time_lock);
		i++;
	}
	if (sim->table.must_eat_count != -1 && all_ate_enough)
	{
		set_sim_stop_flag(&sim->table, true);
		return (true);
	}
	return (false);
}

void	*grim_reaper(void *data)
{
	t_simulation	*sim;

	sim = (t_simulation *)data;
	if (sim->table.must_eat_count == 0)
		return (NULL);
	sim_start_delay(sim->table.start_time);
	while (true)
	{
		if (end_condition_reached(sim))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
