/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:54:49 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:55:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation.h"

pthread_mutex_t	*init_forks(unsigned int count)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

void	destroy_forks(pthread_mutex_t *forks, unsigned int count)
{
	unsigned int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
