#include "renderer.h"
#include "color.h"
#include "config.h"
#include "ft_math.h"
#include "game.h"
#include "orb.h"

#define ORB_DRAW_DESTINATION 0
#define ORB_DRAW_SOURCE 1
#define ORB_DRAW_SURFACE_COUNT 2

static void	draw_orb_pixels(t_rgba_view surfaces[ORB_DRAW_SURFACE_COUNT],
	const t_orb_projection *draw, t_v2i frame, int x)
{
	t_rgba		color;
	t_v2i		texture;
	int			frame_size;
	int			y;

	frame_size = (int)(surfaces[ORB_DRAW_SOURCE].width / ORB_ATLAS_COLUMNS);
	texture.x = frame.x + (x - draw->left) * frame_size / draw->size;
	y = ft_max_int(draw->top, 0);
	while (y <= draw->bottom && y < WINDOW_HEIGHT)
	{
		texture.y = frame.y + (y - draw->top) * frame_size / draw->size;
		color = ft_rgba_read(ft_rgba_view_pixel(&surfaces[ORB_DRAW_SOURCE],
					texture.x, texture.y));
		if (color.alpha > ORB_ALPHA_THRESHOLD)
			blend_pixel(ft_rgba_view_pixel(&surfaces[ORB_DRAW_DESTINATION],
					x, y), color);
		y++;
	}
}

static void	draw_orb_column(t_game *game, const t_orb_projection *draw,
	t_v2i frame, int x)
{
	t_rgba_view	surfaces[ORB_DRAW_SURFACE_COUNT];

	if (draw->depth >= game->ram->sprite_depth[x])
		return ;
	surfaces[ORB_DRAW_DESTINATION] = image_rgba_view(game->frame_buffer);
	surfaces[ORB_DRAW_SOURCE] = texture_rgba_view(game->rom->textures.orb);
	draw_orb_pixels(surfaces, draw, frame, x);
}

void	draw_projected_orb(t_game *game, const t_orb_projection *draw)
{
	mlx_texture_t	*texture;
	t_v2i			frame;
	int				frame_size;
	int				x;

	texture = game->rom->textures.orb;
	frame_size = (int)(texture->width / ORB_ATLAS_COLUMNS);
	frame.x = (int)(game->ram->orbs.animation.index % ORB_ATLAS_COLUMNS)
		* frame_size;
	frame.y = (int)(game->ram->orbs.animation.index / ORB_ATLAS_COLUMNS)
		* frame_size;
	x = draw->left;
	if (x < 0)
		x = 0;
	while (x <= draw->right && x < WINDOW_WIDTH)
	{
		draw_orb_column(game, draw, frame, x);
		x++;
	}
}
