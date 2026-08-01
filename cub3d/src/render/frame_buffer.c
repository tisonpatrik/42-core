#include <stddef.h>
#include "color.h"
#include "game.h"
#include "renderer.h"

void	render_background(t_game *game)
{
	size_t		half_size;
	t_rgba_view	view;

	half_size = (size_t)WINDOW_WIDTH * WINDOW_HEIGHT / 2;
	view = image_rgba_view(game->frame_buffer);
	ft_rgba_fill(ft_rgba_view_pixel(&view, 0, 0), half_size,
		game->rom->ceiling_color);
	ft_rgba_fill(ft_rgba_view_pixel(&view, 0, WINDOW_HEIGHT / 2), half_size,
		game->rom->floor_color);
}

/* Composites a source texel over the already opaque frame buffer. */
void	blend_pixel(t_rgba_ref destination, t_rgba source)
{
	t_rgba	result;

	result = ft_rgba_source_over(source, ft_rgba_read(destination));
	ft_rgba_write(destination, result);
}
