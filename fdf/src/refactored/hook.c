/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:46:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 22:05:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_app		*app;

	app = (t_app *)param;
	if (ydelta > 0)
		app->cam.zoom *= 1.02;
	else if (ydelta < 0 && app->cam.zoom * 0.98 > 0)
		app->cam.zoom *= 0.98;
	xdelta++;
}

static void	reset_map(t_camera *cam)
{
	cam->alpha = 0.46373398 / 2;
	cam->beta = 0.46373398;
	cam->xrotate = 0;
	cam->yrotate = 0;
	cam->zrotate = 0;
	cam->x_offset = WIDTH / 2;
	cam->y_offset = HEIGHT / 2;
	cam->zoom = 1;
	cam->zscale = 1;
}

void	hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_0))
		reset_map(&app->cam);
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->r.mlx);
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_LEFT))
		app->cam.x_offset -= 5;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_RIGHT))
		app->cam.x_offset += 5; 
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_DOWN))
		app->cam.y_offset += 5;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_UP))
		app->cam.y_offset -= 5;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_EQUAL))
		scrollhook(0, 1, param);
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_MINUS))
		scrollhook(0, -1, param);
}

void	hook_project(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_1))
	{
		app->cam.alpha = 0.523599;
		app->cam.beta = app->cam.alpha;
	}
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_2))
	{
		app->cam.alpha = 0.6370452;
		app->cam.beta = app->cam.alpha;
	}
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_3))
	{
		app->cam.alpha = 0.46373398 / 2;
		app->cam.beta = 0.46373398;
	}
}

void	hook_rotate(void *param)
{
	t_app	*app;
	double	sign;

	app = (t_app *) param;
	sign = 0;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(app->r.mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_Q))
		app->cam.alpha += sign * 0.03; 
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_W))
		app->cam.beta += sign * 0.03;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_S))
		app->cam.zscale += sign * 0.03;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_X))
		app->cam.xrotate += sign * 0.02;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_Y))
		app->cam.yrotate += sign * 0.02;
	if (mlx_is_key_down(app->r.mlx, MLX_KEY_Z))
		app->cam.zrotate += sign * 0.02;
}
