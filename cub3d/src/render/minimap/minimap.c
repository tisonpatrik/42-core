#include "renderer.h"
#include "config.h"
#include "ft_math.h"
#include "game.h"
#include "vec2.h"
#include "world.h"

static int	centered_start(int player, int visible, int map_size)
{
	int	start;

	start = player - visible / 2;
	if (start < 0)
		return (0);
	if (start + visible > map_size)
		return (map_size - visible);
	return (start);
}

static t_minimap_view	create_view(t_game *game)
{
	t_minimap_view	view;
	t_v2i			available;
	t_v2i			player;

	available = (t_v2i){MM_MAX_PANEL_WIDTH - MM_PANEL_PADDING * 2,
		MM_MAX_PANEL_HEIGHT - MM_PANEL_PADDING * 2};
	view.tile_scale = ft_min_int(MM_MAX_SCALE,
			ft_min_int(available.x / game->rom->map_size.x,
				available.y / game->rom->map_size.y));
	if (view.tile_scale < MM_MIN_SCALE)
		view.tile_scale = MM_MIN_SCALE;
	view.visible_tiles.x = ft_min_int(game->rom->map_size.x,
			available.x / view.tile_scale);
	view.visible_tiles.y = ft_min_int(game->rom->map_size.y,
			available.y / view.tile_scale);
	player = world_cell(game->ram->player.pos);
	view.first_tile.x = centered_start(player.x, view.visible_tiles.x,
			game->rom->map_size.x);
	view.first_tile.y = centered_start(player.y, view.visible_tiles.y,
			game->rom->map_size.y);
	view.grid_origin.x = WINDOW_WIDTH - MM_MARGIN
		- view.visible_tiles.x * view.tile_scale;
	view.grid_origin.y = MM_MARGIN;
	return (view);
}

static void	draw_grid(t_game *game, t_minimap_view *view)
{
	t_v2i	visible;
	t_v2i	map;
	t_v2i	pixel;

	visible.y = 0;
	while (visible.y < view->visible_tiles.y)
	{
		visible.x = 0;
		while (visible.x < view->visible_tiles.x)
		{
			map = ft_v2i_add(view->first_tile, visible);
			pixel.x = view->grid_origin.x + visible.x * view->tile_scale;
			pixel.y = view->grid_origin.y + visible.y * view->tile_scale;
			minimap_draw_rectangle(game, pixel,
				(t_v2i){view->tile_scale, view->tile_scale},
				minimap_tile_color(game, map));
			visible.x++;
		}
		visible.y++;
	}
}

t_v2i	minimap_world_to_pixel(const t_minimap_view *view, t_v2d position)
{
	t_v2d	relative;
	t_v2i	pixel;

	relative = ft_v2d_sub(position, ft_v2i_to_v2d(view->first_tile));
	pixel.x = view->grid_origin.x + (int)(relative.x * view->tile_scale);
	pixel.y = view->grid_origin.y + (int)(relative.y * view->tile_scale);
	return (pixel);
}

void	render_minimap(t_game *game)
{
	t_minimap_view	view;
	t_v2i			panel_position;
	t_v2i			panel_size;

	view = create_view(game);
	panel_position = (t_v2i){view.grid_origin.x - MM_PANEL_PADDING,
		view.grid_origin.y - MM_PANEL_PADDING};
	panel_size.x = view.visible_tiles.x * view.tile_scale
		+ MM_PANEL_PADDING * 2;
	panel_size.y = view.visible_tiles.y * view.tile_scale
		+ MM_PANEL_PADDING * 2;
	minimap_draw_rectangle(game, panel_position, panel_size,
		minimap_color(MM_COLOR_PANEL));
	draw_grid(game, &view);
	minimap_draw_orbs(game, &view);
	minimap_draw_player(game, &view);
}
