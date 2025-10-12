/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:10:37 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 21:58:28 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_app		*app;

	app = (t_app *)param;
	if (ydelta > 0)
		app->view->zoom *= 1.02;
	else if (ydelta < 0 && app->view->zoom * 0.98 > 0)
		app->view->zoom *= 0.98;
	xdelta++;
}

static void	reset_map(t_view *view)
{
	view->alpha = 0.46373398 / 2;
	view->beta = 0.46373398;
	view->xrotate = 0;
	view->yrotate = 0;
	view->zrotate = 0;
	view->x_offset = WIDTH / 2;
	view->y_offset = HEIGHT / 2;
	view->zoom = 1;
	view->zscale = 1;
}

void	handle_keybinds(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_0))
		reset_map(app->view);
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		app->view->x_offset -= 5;
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		app->view->x_offset += 5; 
	if (mlx_is_key_down(app->mlx, MLX_KEY_DOWN))
		app->view->y_offset += 5;
	if (mlx_is_key_down(app->mlx, MLX_KEY_UP))
		app->view->y_offset -= 5;
	if (mlx_is_key_down(app->mlx, MLX_KEY_EQUAL))
		handle_scroll(0, 1, param);
	if (mlx_is_key_down(app->mlx, MLX_KEY_MINUS))
		handle_scroll(0, -1, param);
}

void	handle_projection(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_1))
	{
		app->view->alpha = 0.523599;
		app->view->beta = app->view->alpha;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_2))
	{
		app->view->alpha = 0.6370452;
		app->view->beta = app->view->alpha;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_3))
	{
		app->view->alpha = 0.46373398 / 2;
		app->view->beta = 0.46373398;
	}
}

void	handle_rotate(void *param)
{
	t_app	*app;
	double	sign;

	app = (t_app *) param;
	sign = 0;
	if (mlx_is_key_down(app->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(app->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(app->mlx, MLX_KEY_Q))
		app->view->alpha += sign * 0.03; 
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
		app->view->beta += sign * 0.03;
	if (mlx_is_key_down(app->mlx, MLX_KEY_S))
		app->view->zscale += sign * 0.03;
	if (mlx_is_key_down(app->mlx, MLX_KEY_X))
		app->view->xrotate += sign * 0.02;
	if (mlx_is_key_down(app->mlx, MLX_KEY_Y))
		app->view->yrotate += sign * 0.02;
	if (mlx_is_key_down(app->mlx, MLX_KEY_Z))
		app->view->zrotate += sign * 0.02;
}
