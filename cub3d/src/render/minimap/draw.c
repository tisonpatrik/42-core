#include "renderer.h"
#include "ft_math.h"
#include "game.h"
#include "fire.h"
#include "vec2.h"
#include "world.h"

t_rgba	minimap_color(t_minimap_color color)
{
	if (color == MM_COLOR_PANEL)
		return (ft_rgba_create(16, 24, 32, FT_COLOR_CHANNEL_MAX));
	if (color == MM_COLOR_WALL)
		return (ft_rgba_create(204, 204, 204, FT_COLOR_CHANNEL_MAX));
	if (color == MM_COLOR_FLOOR)
		return (ft_rgba_create(38, 49, 60, FT_COLOR_CHANNEL_MAX));
	if (color == MM_COLOR_FIRE)
		return (ft_rgba_create(255, 122, 24, FT_COLOR_CHANNEL_MAX));
	if (color == MM_COLOR_SCORCH)
		return (ft_rgba_create(90, 53, 32, FT_COLOR_CHANNEL_MAX));
	if (color == MM_COLOR_PLAYER)
		return (ft_rgba_create(255, 51, 51, FT_COLOR_CHANNEL_MAX));
	return (ft_rgba_create(255, 213, 74, FT_COLOR_CHANNEL_MAX));
}

void	minimap_draw_rectangle(t_game *game, t_v2i position,
	t_v2i size, t_rgba color)
{
	t_rgba_view	view;
	t_v2i		first;
	t_v2i		last;
	t_v2i		pixel;

	view = image_rgba_view(game->frame_buffer);
	first.x = ft_clamp_int(position.x, 0, (int)view.width);
	first.y = ft_clamp_int(position.y, 0, (int)view.height);
	last.x = ft_clamp_int(position.x + size.x, 0, (int)view.width);
	last.y = ft_clamp_int(position.y + size.y, 0, (int)view.height);
	pixel.y = first.y;
	while (pixel.y < last.y)
	{
		pixel.x = first.x;
		while (pixel.x < last.x)
		{
			ft_rgba_write(ft_rgba_view_pixel(&view, pixel.x, pixel.y), color);
			pixel.x++;
		}
		pixel.y++;
	}
}

t_rgba	minimap_tile_color(t_game *game, t_v2i map)
{
	t_tile	tile;

	tile = world_tile(game, map);
	if (tile == TILE_WALL)
		return (minimap_color(MM_COLOR_WALL));
	if (tile == TILE_VOID)
		return (minimap_color(MM_COLOR_PANEL));
	if (tile != TILE_FIRE)
		return (minimap_color(MM_COLOR_FLOOR));
	if (fire_height_at(game, map) > 0.0)
		return (minimap_color(MM_COLOR_FIRE));
	return (minimap_color(MM_COLOR_SCORCH));
}

void	minimap_draw_player(t_game *game, t_minimap_view *view)
{
	t_v2i	position;
	int		size;
	int		half_size;

	size = view->tile_scale / 2;
	size = ft_max_int(size, 2);
	half_size = size / 2;
	position = minimap_world_to_pixel(view, game->ram->player.pos);
	position.x -= half_size;
	position.y -= half_size;
	minimap_draw_rectangle(game, position, (t_v2i){size, size},
		minimap_color(MM_COLOR_PLAYER));
}
