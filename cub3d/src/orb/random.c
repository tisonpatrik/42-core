/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:47 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orb.h"
#include <stddef.h>
#include <sys/time.h>
#include "game.h"

/* The PRNG mixes these readable entropy sources when producing values. */
uint32_t	orb_seed(t_game *game)
{
	struct timeval	time;
	uint32_t		seed;

	seed = (uint32_t)game->rom->map_size.x;
	seed += (uint32_t)game->rom->map_size.y;
	if (gettimeofday(&time, NULL) == 0)
	{
		seed += (uint32_t)time.tv_sec;
		seed += (uint32_t)time.tv_usec;
	}
	return (seed);
}
