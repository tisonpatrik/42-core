#include "renderer.h"
#include "config.h"
#include "ft_math.h"
#include "game.h"

void	calc_wall_projection(t_draw *draw, double distance)
{
	int	screen_center;
	int	half_wall;

	if (distance < RENDER_NEAR_DISTANCE)
		distance = RENDER_NEAR_DISTANCE;
	draw->projected_height = (int)(WINDOW_HEIGHT / distance);
	draw->projected_height = ft_max_int(draw->projected_height, 1);
	screen_center = WINDOW_HEIGHT / 2;
	half_wall = draw->projected_height / 2;
	draw->screen_top = screen_center - half_wall;
	draw->screen_top = ft_max_int(draw->screen_top, 0);
	draw->screen_bottom = screen_center + half_wall;
	draw->screen_bottom = ft_clamp_int(draw->screen_bottom, 0,
			WINDOW_HEIGHT - 1);
}

/* The face normal points opposite to the ray's direction of travel. */
mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->wall.side == HIT_X)
	{
		if (ray->dir.x < 0.0)
			return (game->rom->textures.wall[TEX_EAST]);
		return (game->rom->textures.wall[TEX_WEST]);
	}
	if (ray->dir.y < 0.0)
		return (game->rom->textures.wall[TEX_SOUTH]);
	return (game->rom->textures.wall[TEX_NORTH]);
}

int	texture_column(const t_ray_hit *hit, t_v2d direction, int width)
{
	int	column;

	column = (int)(hit->wall_x * width);
	if ((hit->side == HIT_X && direction.x > 0.0)
		|| (hit->side == HIT_Y && direction.y < 0.0))
		column = width - column - 1;
	return (ft_clamp_int(column, 0, width - 1));
}

void	calc_texture_mapping(t_draw *draw, t_ray *ray,
	mlx_texture_t *texture)
{
	double	clipped;

	draw->texture_x = texture_column(&ray->wall, ray->dir,
			(int)texture->width);
	draw->texture_y_step = (double)texture->height
		/ draw->projected_height;
	clipped = 0.0;
	if (draw->projected_height > WINDOW_HEIGHT)
		clipped = (draw->projected_height - WINDOW_HEIGHT) / 2.0;
	draw->texture_y_position = clipped * draw->texture_y_step;
}

void	draw_wall_column(t_game *game, int x, t_draw *draw,
	mlx_texture_t *texture)
{
	t_rgba_view	frame;
	t_rgba_view	source;
	int			y;

	frame = image_rgba_view(game->frame_buffer);
	source = texture_rgba_view(texture);
	y = draw->screen_top;
	while (y <= draw->screen_bottom)
	{
		draw->texture_y = (int)draw->texture_y_position
			% (int)texture->height;
		draw->texture_y_position += draw->texture_y_step;
		ft_rgba_copy(ft_rgba_view_pixel(&frame, x, y),
			ft_rgba_view_pixel(&source, draw->texture_x, draw->texture_y));
		y++;
	}
}
