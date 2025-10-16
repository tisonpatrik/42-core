/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:47:57 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:02:21 by ptison            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/old_app.h"

/* ========================================================================== */
/* PROJECTION FUNCTIONS - On-the-fly 3D to 2D conversion                    */
/* ========================================================================== */

t_point2d_temp	project_point(t_point3d point, t_view *view)
{
	t_point2d_temp	result;
	double			temp_x;
	double			temp_y;
	double			temp_z;

	temp_x = point.x;
	temp_y = point.y;
	temp_z = point.z * view->camera.zscale;
	
	/* Apply rotations */
	rotate_z(&temp_x, &temp_y, view->camera.zrotate);
	rotate_x(&temp_y, &temp_z, view->camera.xrotate);
	rotate_y(&temp_x, &temp_z, view->camera.yrotate);
	
	/* Project to 2D screen coordinates */
	result.x = (int)((temp_x * view->camera.zoom - temp_y * view->camera.zoom)
			* cos(view->camera.alpha) + view->camera.x_offset);
	result.y = (int)(-temp_z * view->camera.zoom
			+ (temp_x * view->camera.zoom + temp_y * view->camera.zoom)
			* sin(view->camera.beta) + view->camera.y_offset);
	result.rgba = point.zcolor;
	
	return (result);
}

/* ========================================================================== */
/* DRAWING FUNCTIONS - Optimized Bresenham with on-the-fly projection       */
/* ========================================================================== */

static void	bresenham(mlx_image_t *image, t_point3d a_3d, t_point3d b_3d, t_view *view)
{
	t_point2d_temp	a;
	t_point2d_temp	b;
	t_point2d_temp	cur;
	int				error[2];

	/* Project 3D points to 2D on-the-fly */
	a = project_point(a_3d, view);
	b = project_point(b_3d, view);
	
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

static void	draw_line(t_fdf *fdf, int x, int y)
{
	t_point3d	*current;
	t_point3d	*right;
	t_point3d	*down;

	current = &(fdf->view->grid.grid3d[y][x]);
	
	/* Draw vertical line (down) */
	if (y + 1 < fdf->view->grid.rows)
	{
		down = &(fdf->view->grid.grid3d[y + 1][x]);
		bresenham(fdf->image, *current, *down, fdf->view);
	}
	
	/* Draw horizontal line (right) */
	if (x + 1 < fdf->view->grid.cols)
	{
		right = &(fdf->view->grid.grid3d[y][x + 1]);
		bresenham(fdf->image, *current, *right, fdf->view);
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
	while (++i < fdf->view->grid.rows)
	{
		j = -1;
		while (++j < fdf->view->grid.cols)
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