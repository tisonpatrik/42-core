/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:57:38 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:57:44 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophy.h"

static void	free_philosophers_array(t_philosopher **philos, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		if (philos[i])
		{
			pthread_mutex_destroy(&philos[i]->meal_time_lock);
			free(philos[i]);
		}
		i++;
	}
	free(philos);
}

static void	assign_forks(t_philosopher *philo)
{
	philo->fork_left = philo->id;
	philo->fork_right = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		philo->fork_left = (philo->id + 1) % philo->table->nb_philos;
		philo->fork_right = philo->id;
	}
}

static t_philosopher	*init_single_philosopher(t_table *table,
		unsigned int id)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	if (pthread_mutex_init(&philo->meal_time_lock, 0) != 0)
	{
		free(philo);
		return (NULL);
	}
	philo->table = table;
	philo->id = id;
	philo->times_ate = 0;
	philo->last_meal = 0;
	assign_forks(philo);
	return (philo);
}

t_philosopher	**init_philosophers(t_table *table)
{
	t_philosopher	**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philosopher *) * table->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = init_single_philosopher(table, i);
		if (!philos[i])
		{
			free_philosophers_array(philos, i);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

void	destroy_philosophers(t_philosopher **philos, unsigned int count)
{
	if (!philos)
		return ;
	free_philosophers_array(philos, count);
}
