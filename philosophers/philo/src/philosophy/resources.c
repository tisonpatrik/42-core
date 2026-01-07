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
	int	first_fork_id;
	int	second_fork_id;

	if (philo->fork_left < philo->fork_right)
	{
		first_fork_id = philo->fork_left;
		second_fork_id = philo->fork_right;
	}
	else
	{
		first_fork_id = philo->fork_right;
		second_fork_id = philo->fork_left;
	}
	pthread_mutex_lock(&philo->table->fork_locks[first_fork_id]);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[second_fork_id]);
	write_status(philo, "has taken a fork");
}

void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_right]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork_left]);
}
