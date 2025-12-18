/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resources.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:57:07 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:57:09 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophy.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork_right]);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
		write_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork_left]);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->fork_locks[philo->fork_right]);
		write_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_right]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_left]);
}
