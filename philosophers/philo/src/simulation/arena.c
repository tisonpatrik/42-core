/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:56:13 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:56:22 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

static bool	init_table(t_table *table, t_inputs inputs)
{
	table->nb_philos = inputs.nb_philos;
	table->time_to_die = inputs.time_to_die;
	table->time_to_eat = inputs.time_to_eat;
	table->time_to_sleep = inputs.time_to_sleep;
	table->must_eat_count = inputs.must_eat_count;
	table->have_eat_count = inputs.have_eat_count;
	table->sim_stop = false;
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (false);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
	{
		pthread_mutex_destroy(&table->sim_stop_lock);
		return (false);
	}
	table->fork_locks = init_forks(table->nb_philos);
	if (!table->fork_locks)
	{
		pthread_mutex_destroy(&table->write_lock);
		pthread_mutex_destroy(&table->sim_stop_lock);
		return (false);
	}
	return (true);
}

t_result	create_simulation(t_inputs inputs)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return ((t_result){NULL, false});
	if (!init_table(&sim->table, inputs))
	{
		free(sim);
		return ((t_result){NULL, false});
	}
	sim->philos = init_philosophers(&sim->table);
	if (!sim->philos)
	{
		destroy_forks(sim->table.fork_locks, sim->table.nb_philos);
		pthread_mutex_destroy(&sim->table.write_lock);
		pthread_mutex_destroy(&sim->table.sim_stop_lock);
		free(sim);
		return ((t_result){NULL, false});
	}
	return ((t_result){sim, true});
}

void	destroy_simulation(t_simulation *sim)
{
	if (!sim)
		return ;
	destroy_philosophers(sim->philos, sim->table.nb_philos);
	destroy_forks(sim->table.fork_locks, sim->table.nb_philos);
	pthread_mutex_destroy(&sim->table.write_lock);
	pthread_mutex_destroy(&sim->table.sim_stop_lock);
	free(sim);
}
