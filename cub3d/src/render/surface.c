#include "renderer.h"
#include "color.h"

t_rgba_view	image_rgba_view(mlx_image_t *image)
{
	return ((t_rgba_view){image->pixels, image->width, image->height,
		(size_t)image->width * FT_RGBA_CHANNEL_COUNT});
}

t_rgba_view	texture_rgba_view(mlx_texture_t *texture)
{
	return ((t_rgba_view){texture->pixels, texture->width, texture->height,
		(size_t)texture->width * FT_RGBA_CHANNEL_COUNT});
}
