#include "renderer.h"
#include <math.h>
#include "config.h"
#include "game.h"
#include "world.h"

static void	init_ray(t_ray *ray, t_player *player, int screen_x)
{
	double	x;

	x = 2.0 * screen_x / (double)WINDOW_WIDTH - 1.0;
	ray->dir = ft_v2d_add(player->dir, ft_v2d_scale(player->plane, x));
	ray->map = world_cell(player->pos);
	ray->delta_dist = (t_v2d){DELTA_INFINITY, DELTA_INFINITY};
	if (ray->dir.x != 0.0)
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y != 0.0)
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

/* Precomputes the distance from the player to the first X/Y grid boundary. */
static void	init_steps(t_ray *ray, t_player *player)
{
	ray->step = (t_v2i){1, 1};
	if (ray->dir.x < 0.0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
		ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	if (ray->dir.y < 0.0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
		ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
}

static t_hit_side	advance_ray(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		return (HIT_X);
	}
	ray->side_dist.y += ray->delta_dist.y;
	ray->map.y += ray->step.y;
	return (HIT_Y);
}

static t_ray_hit	make_hit(t_ray *ray, t_player *player, t_hit_side side)
{
	t_ray_hit	hit;

	hit.map = ray->map;
	hit.side = side;
	if (side == HIT_X)
	{
		hit.distance = ray->side_dist.x - ray->delta_dist.x;
		hit.wall_x = player->pos.y + hit.distance * ray->dir.y;
	}
	else
	{
		hit.distance = ray->side_dist.y - ray->delta_dist.y;
		hit.wall_x = player->pos.x + hit.distance * ray->dir.x;
	}
	hit.wall_x -= floor(hit.wall_x);
	return (hit);
}

/* DDA visits one map cell at a time and cannot escape world_tile bounds. */
void	cast_ray(t_game *game, int screen_x, t_ray *ray, t_hit_buffer *hits)
{
	t_hit_side	side;
	t_ray_hit	hit;
	t_tile		tile;

	init_ray(ray, &game->ram->player, screen_x);
	init_steps(ray, &game->ram->player);
	hits->count = 0;
	while (true)
	{
		side = advance_ray(ray);
		hit = make_hit(ray, &game->ram->player, side);
		tile = world_tile(game, ray->map);
		if (world_blocks_ray(game, ray->map))
			break ;
		if (tile == TILE_FIRE && hits->count < hits->capacity)
			hits->items[hits->count++] = hit;
	}
	ray->wall = hit;
}
