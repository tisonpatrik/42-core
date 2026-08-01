#include "input.h"
#include "game.h"
#include "world.h"

static double	leading_edge(double coordinate, double movement)
{
	if (movement < 0.0)
		return (coordinate - COLLISION_MARGIN);
	return (coordinate + COLLISION_MARGIN);
}

/* Both circle edges are checked so corners cannot clip the player. */
static bool	can_move_x(t_game *game, t_v2d candidate, double movement)
{
	t_v2d	check;

	check.x = leading_edge(candidate.x, movement);
	check.y = candidate.y - COLLISION_MARGIN;
	if (world_is_solid(game, world_cell(check)))
		return (false);
	check.y = candidate.y + COLLISION_MARGIN;
	return (!world_is_solid(game, world_cell(check)));
}

static bool	can_move_y(t_game *game, t_v2d candidate, double movement)
{
	t_v2d	check;

	check.x = candidate.x - COLLISION_MARGIN;
	check.y = leading_edge(candidate.y, movement);
	if (world_is_solid(game, world_cell(check)))
		return (false);
	check.x = candidate.x + COLLISION_MARGIN;
	return (!world_is_solid(game, world_cell(check)));
}

void	move_player(t_game *game, t_v2d movement)
{
	t_player	*player;
	t_v2d		candidate;

	player = &game->ram->player;
	candidate = player->pos;
	candidate.x += movement.x;
	if (movement.x != 0.0 && can_move_x(game, candidate, movement.x))
		player->pos.x = candidate.x;
	candidate = player->pos;
	candidate.y += movement.y;
	if (movement.y != 0.0 && can_move_y(game, candidate, movement.y))
		player->pos.y = candidate.y;
}
