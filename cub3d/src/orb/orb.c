#include "orb.h"
#include <stdlib.h>
#include "game.h"
#include "io.h"

int	orb_init(t_game *game)
{
	if (!orb_generate(game, orb_seed(game)))
	{
		ft_putendl_fd("Error\nFailed to generate experience orbs.", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	orb_update_animation(t_orb_system *system, double delta_time)
{
	if (system->count == system->collected)
		return ;
	ft_step_cycle_advance(&system->animation, delta_time,
		ORB_FRAME_INTERVAL, ORB_FRAME_COUNT);
}

void	orb_update(t_game *game, double delta_time)
{
	orb_update_animation(&game->ram->orbs, delta_time);
	orb_collect_nearby(game);
}
