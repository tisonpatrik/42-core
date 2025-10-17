/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:46:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 01:05:41 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_app		*app;

	app = (t_app *)param;
	if (ydelta > 0)
		app->camera.zoom *= 1.02;
	else if (ydelta < 0 && app->camera.zoom * 0.98 > 0)
		app->camera.zoom *= 0.98;
	xdelta++;
}

void	hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_0))
		reset_camera(&app->camera, app->renderer.width, app->renderer.height);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->renderer.mlx);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_LEFT))
		app->camera.x_offset -= 5;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_RIGHT))
		app->camera.x_offset += 5; 
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_DOWN))
		app->camera.y_offset += 5;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_UP))
		app->camera.y_offset -= 5;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_EQUAL))
		scrollhook(0, 1, param);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_MINUS))
		scrollhook(0, -1, param);
}

void	hook_project(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_1))
	{
		app->camera.alpha = 0.523599;
		app->camera.beta = app->camera.alpha;
	}
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_2))
	{
		app->camera.alpha = 0.6370452;
		app->camera.beta = app->camera.alpha;
	}
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_3))
	{
		app->camera.alpha = 0.46373398 / 2;
		app->camera.beta = 0.46373398;
	}
}

void	hook_rotate(void *param)
{
	t_app	*app;
	double	sign;

	app = (t_app *) param;
	sign = 0;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_Q))
		app->camera.alpha += sign * 0.03; 
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_W))
		app->camera.beta += sign * 0.03;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_S))
		app->camera.zscale += sign * 0.03;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_X))
		app->camera.xrotate += sign * 0.02;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_Y))
		app->camera.yrotate += sign * 0.02;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_Z))
		app->camera.zrotate += sign * 0.02;
}
