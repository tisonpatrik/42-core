/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:50 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orb.h"
#include "game.h"
#include "prng.h"
#include "world.h"

static void	shuffle_candidates(t_v2i *items, size_t count, t_prng *prng)
{
	size_t	i;
	size_t	other;
	t_v2i	temporary;

	i = count;
	while (i > 1)
	{
		i--;
		other = ft_prng_bounded(prng, i + 1);
		temporary = items[i];
		items[i] = items[other];
		items[other] = temporary;
	}
}

static void	prioritize_near_spawn(t_game *game, t_v2i *items, size_t count)
{
	t_v2i	spawn;
	t_v2i	temporary;
	size_t	i;
	double	distance;

	spawn = world_cell(game->ram->player.pos);
	i = 0;
	while (i < count)
	{
		distance = ft_v2i_distance_squared(spawn, items[i]);
		if (distance >= ORB_NEAR_MIN_DISTANCE_SQUARED
			&& distance <= ORB_NEAR_MAX_DISTANCE_SQUARED)
		{
			temporary = items[0];
			items[0] = items[i];
			items[i] = temporary;
			return ;
		}
		i++;
	}
}

static bool	far_enough(t_orb_system *system, t_v2i candidate,
	double minimum_squared)
{
	t_v2i	position;
	size_t	i;
	double	distance;

	i = 0;
	while (i < system->count)
	{
		position = world_cell(system->orbs[i].position);
		distance = ft_v2i_distance_squared(position, candidate);
		if (distance == 0.0 || distance < minimum_squared)
			return (false);
		i++;
	}
	return (true);
}

static void	fill_positions(t_orb_system *system, t_v2i *items, size_t count,
	double minimum_squared)
{
	size_t	desired;
	size_t	i;
	t_orb	*orb;

	desired = count / ORB_CANDIDATES_PER_ORB;
	if (count % ORB_CANDIDATES_PER_ORB != 0)
		desired++;
	if (desired > ORB_MAX_COUNT)
		desired = ORB_MAX_COUNT;
	i = 0;
	while (i < count && system->count < desired)
	{
		if (far_enough(system, items[i], minimum_squared))
		{
			orb = &system->orbs[system->count++];
			orb->position = world_cell_center(items[i]);
			orb->active = true;
		}
		i++;
	}
}

/* One orb per started hundred candidates, clamped by ORB_MAX_COUNT. */
size_t	orb_select_positions(t_game *game, t_v2i *items, size_t count,
	uint32_t seed)
{
	t_orb_system	*system;
	t_prng			prng;

	system = &game->ram->orbs;
	system->count = 0;
	if (count == 0)
		return (0);
	prng = ft_prng_create(seed);
	shuffle_candidates(items, count, &prng);
	prioritize_near_spawn(game, items, count);
	fill_positions(system, items, count, ORB_MIN_SPACING_SQUARED);
	fill_positions(system, items, count, 0.0);
	return (system->count);
}
