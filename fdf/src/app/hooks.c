/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:46:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 01:16:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/old_app.h"

void	fdf_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *)param;
	if (ydelta > 0)
		fdf->view->camera.zoom *= 1.02;
	else if (ydelta < 0 && fdf->view->camera.zoom * 0.98 > 0)
		fdf->view->camera.zoom *= 0.98;
	xdelta++;
}

static void	reset_map(t_view *view)
{
	view->camera.alpha = 0.46373398 / 2;
	view->camera.beta = 0.46373398;
	view->camera.xrotate = 0;
	view->camera.yrotate = 0;
	view->camera.zrotate = 0;
	view->camera.x_offset = WIDTH / 2;
	view->camera.y_offset = HEIGHT / 2;
	view->camera.zoom = 1;
	view->camera.zscale = 1;
}

void	ft_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		reset_map(fdf->view);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->view->camera.x_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->view->camera.x_offset += 5; 
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->view->camera.y_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->view->camera.y_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf_scrollhook(0, 1, param);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf_scrollhook(0, -1, param);
}

void	ft_hook_project(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
	{
		fdf->view->camera.alpha = 0.523599;
		fdf->view->camera.beta = fdf->view->camera.alpha;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
	{
		fdf->view->camera.alpha = 0.6370452;
		fdf->view->camera.beta = fdf->view->camera.alpha;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		fdf->view->camera.alpha = 0.46373398 / 2;
		fdf->view->camera.beta = 0.46373398;
	}
}

void	ft_hook_rotate(void *param)
{
	t_fdf	*fdf;
	double	sign;

	fdf = (t_fdf *) param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->view->camera.alpha += sign * 0.03; 
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->view->camera.beta += sign * 0.03;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->view->camera.zscale += sign * 0.03;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
		fdf->view->camera.xrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		fdf->view->camera.yrotate += sign * 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		fdf->view->camera.zrotate += sign * 0.02;
}
