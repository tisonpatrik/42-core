#include "renderer.h"
#include "config.h"
#include "game.h"
#include "fire.h"

/* Camera height is half a tile, hence 0.5 * screen height. */
static void	init_floor_distances(double *distances)
{
	int	i;
	int	y;

	i = 0;
	y = WINDOW_HEIGHT / 2 + 1;
	while (i < FLOOR_ROW_COUNT)
	{
		distances[i] = (0.5 * WINDOW_HEIGHT)
			/ (y - WINDOW_HEIGHT / 2.0);
		i++;
		y++;
	}
}

static void	render_fire_hits(t_game *game, int x, t_ray *ray)
{
	t_hit_buffer	*hits;
	size_t			i;

	hits = &game->ram->fire_hits;
	i = hits->count;
	while (i > 0)
	{
		i--;
		draw_fire_column(game, x, ray, &hits->items[i]);
	}
}

/* Closed fire gates join walls in the orb's per-column depth test. */
static double	nearest_sprite_occluder(t_game *game, t_ray *ray)
{
	double	depth;
	size_t	i;

	depth = ray->wall.distance;
	i = 0;
	while (i < game->ram->fire_hits.count)
	{
		if (fire_height_at(game, game->ram->fire_hits.items[i].map) > 0.0
			&& game->ram->fire_hits.items[i].distance < depth)
			depth = game->ram->fire_hits.items[i].distance;
		i++;
	}
	return (depth);
}

static void	render_column(t_game *game, int x, const double *distances)
{
	t_ray			ray;
	t_draw			draw;
	mlx_texture_t	*texture;

	cast_ray(game, x, &ray, &game->ram->fire_hits);
	if (game->rom->bonus_enabled)
		game->ram->sprite_depth[x] = nearest_sprite_occluder(game, &ray);
	calc_wall_projection(&draw, ray.wall.distance);
	texture = get_wall_texture(game, &ray);
	calc_texture_mapping(&draw, &ray, texture);
	draw_wall_column(game, x, &draw, texture);
	if (game->rom->bonus_enabled && game->ram->fire.count > 0)
		render_scorch_column(game, x, &ray, distances);
	if (game->rom->bonus_enabled)
		render_fire_hits(game, x, &ray);
}

void	render_frame(t_game *game)
{
	double	floor_distances[FLOOR_ROW_COUNT];
	int		x;

	if (game->rom->bonus_enabled && game->ram->fire.count > 0)
		init_floor_distances(floor_distances);
	render_background(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		render_column(game, x, floor_distances);
		x++;
	}
	if (game->rom->bonus_enabled)
	{
		render_orbs(game);
		render_minimap(game);
	}
}
