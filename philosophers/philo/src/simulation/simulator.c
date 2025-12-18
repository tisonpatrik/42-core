/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:54:20 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:54:23 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

char	*start_simulation(t_simulation *sim)
{
	unsigned int	i;

	sim->table.start_time = get_time_in_ms() + (sim->table.nb_philos * 2 * 10);
	i = 0;
	while (i < sim->table.nb_philos)
	{
		if (pthread_create(&sim->philos[i]->thread, NULL, &do_philosophy,
				sim->philos[i]) != 0)
			return ("Thread creation failed");
		i++;
	}
	if (sim->table.nb_philos > 1)
	{
		if (pthread_create(&sim->grim_reaper, NULL, &grim_reaper, sim) != 0)
			return ("Thread creation failed");
	}
	return (NULL);
}

void	stop_simulation(t_simulation *sim)
{
	unsigned int	i;
	unsigned int	full_count;

	i = 0;
	while (i < sim->table.nb_philos)
	{
		pthread_join(sim->philos[i]->thread, NULL);
		i++;
	}
	if (sim->table.nb_philos > 1)
		pthread_join(sim->grim_reaper, NULL);
	if (sim->table.have_eat_count)
	{
		full_count = 0;
		i = 0;
		while (i < sim->table.nb_philos)
		{
			if (sim->philos[i]->times_ate >= sim->table.must_eat_count)
				full_count++;
			i++;
		}
		printf("%d/%d philosophers had at least %d meals.\n", full_count,
			sim->table.nb_philos, sim->table.must_eat_count);
	}
}
