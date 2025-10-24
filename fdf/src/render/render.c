/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:50:28 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 18:18:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

t_renderer	init_renderer(void)
{
	t_renderer	renderer;

	renderer.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	renderer.img = mlx_new_image(renderer.mlx, WIDTH, HEIGHT);
	renderer.width = WIDTH;
	renderer.height = HEIGHT;
	return (renderer);
}

static void	draw_clear(mlx_image_t *image, uint32_t color)
{
	size_t		count_of_pixels;
	uint32_t	*pixels;
	size_t		i;

	count_of_pixels = (size_t)image->width * image->height;
	pixels = (uint32_t *)image->pixels;
	i = 0;
	while (i < count_of_pixels)
	{
		pixels[i] = color;
		i++;
	}
}

void	render_image(mlx_image_t *image, t_grid *grid)
{
	t_render_grid	render_grig;
	int				y;

	draw_clear(image, BACKGROUND);
	render_grig = create_render_grid(grid);
	if (!render_grig.points)
		return ;
	y = 0;
	while (y < render_grig.rows)
	{
		draw_grid_row(image, &render_grig, y);
		y++;
	}
	free_render_grid(&render_grig);
}
