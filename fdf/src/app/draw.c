/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:47:57 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:02:21 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

static void	bresenham(mlx_image_t *image, t_point2d a, t_point2d b)
{
	int			error[2];
	t_point2d	cur;

	cur.x = a.x;
	cur.y = a.y;
	error[0] = abs(b.x - a.x) - abs(b.y - a.y);
	while (cur.x != b.x || cur.y != b.y)
	{
		if ((uint32_t)cur.x < image->width && (uint32_t)cur.y < image->height)
			mlx_put_pixel(image, cur.x, cur.y, get_color(cur, a, b));
		error[1] = 2 * error[0];
		if (error[1] > -abs(b.y - a.y))
		{
			error[0] -= abs(b.y - a.y);
			cur.x += (a.x < b.x);
			cur.x -= (b.x < a.x);
		}
		if (error[1] < abs(b.x - a.x))
		{
			error[0] += abs(b.x - a.x);
			cur.y += (a.y < b.y);
			cur.y -= (b.y < a.y);
		}
	}
}

void	project(t_view *map, int i, int j)
{
	t_point3d	*previous;
	t_point3d	temp;
	t_point2d	*new;

	previous = &(map->grid.grid3d[i][j]);
	new = &(map->grid.grid2d[i][j]);
	temp.x = previous->x;
	temp.y = previous->y;
	temp.z = previous->z * map->camera.zscale;
	rotate_z(&temp.x, &temp.y, map->camera.zrotate);
	rotate_x(&temp.y, &temp.z, map->camera.xrotate);
	rotate_y(&temp.x, &temp.z, map->camera.yrotate);
	new->x = (int)((temp.x * map->camera.zoom - temp.y * map->camera.zoom)
			* cos(map->camera.alpha) + map->camera.x_offset);
	new->y = (int)(-temp.z * map->camera.zoom
			+ (temp.x * map->camera.zoom + temp.y * map->camera.zoom)
			* sin(map->camera.beta) + map->camera.y_offset);
	new->rgba = previous->zcolor;
}

static void	draw_line(t_fdf *fdf, int x, int y)
{
	if (y == 0 && x == 0)
		project(fdf->map, y, x);
	if (y + 1 < fdf->map->grid_info.rows)
	{
		project(fdf->map, y + 1, x);
		bresenham(fdf->image, fdf->map->grid.grid2d[y][x],
			fdf->map->grid.grid2d[y + 1][x]);
	}
	if (x + 1 < fdf->map->grid_info.cols)
	{
		if (y == 0)
			project(fdf->map, y, x + 1);
		bresenham(fdf->image, fdf->map->grid.grid2d[y][x],
			fdf->map->grid.grid2d[y][x + 1]);
	}
}

void	draw_image(void *param)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	draw_reset(fdf->image);
	i = -1;
	while (++i < fdf->map->grid_info.rows)
	{
		j = -1;
		while (++j < fdf->map->grid_info.cols)
			draw_line(fdf, j, i);
	}
}

void	display_menu(mlx_t *mlx)
{
	int		x;
	int		y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Zoom\t\t\t\t\t\t\t\t\t\tmouse scroll or -+", x, y += 35);
	mlx_put_string(mlx, "Translate\t\t\t\t\tarrow keys", x, y += 20);
	mlx_put_string(mlx, "Scale z\t\t\t\t\t\t\ts + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate x\t\t\t\t\t\tx + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate y\t\t\t\t\t\ty + </>", x, y += 20);
	mlx_put_string(mlx, "Rotate z\t\t\t\t\t\tz + </>", x, y += 20);
	mlx_put_string(mlx, "PROJECTION", x, y += 30);
	mlx_put_string(mlx, "Angle x\t\t\t\t\t\t\tq + </>", x, y += 25);
	mlx_put_string(mlx, "Angle y\t\t\t\t\t\t\tw + </>", x, y += 20);
	mlx_put_string(mlx, "Isometric\t\t\t\t\t1", x, y += 20);
	mlx_put_string(mlx, "Dimetric\t\t\t\t\t\t2", x, y += 20);
	mlx_put_string(mlx, "Trimetric\t\t\t\t\t3", x, y += 20);
	mlx_put_string(mlx, "RESET\t\t\t\t\t\t\t\t\t0", x, y += 30);
}
