#include "orb.h"
#include "game.h"

static void	collect_orb(t_orb_system *system, t_orb *orb)
{
	orb->active = false;
	system->collected++;
}

void	orb_collect_nearby(t_game *game)
{
	t_orb_system	*system;
	size_t			i;

	system = &game->ram->orbs;
	i = 0;
	while (i < system->count)
	{
		if (system->orbs[i].active
			&& ft_v2d_distance_squared(system->orbs[i].position,
				game->ram->player.pos) <= ORB_PICKUP_RADIUS
			* ORB_PICKUP_RADIUS)
			collect_orb(system, &system->orbs[i]);
		i++;
	}
}
