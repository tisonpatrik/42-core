/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:46:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 09:51:23 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

void	hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->renderer.mlx);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_LEFT))
		app->camera.x_offset = ft_max(-WIDTH, app->camera.x_offset - 5);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_RIGHT))
		app->camera.x_offset = ft_min(WIDTH * 2, app->camera.x_offset + 5);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_DOWN))
		app->camera.y_offset = ft_min(HEIGHT * 2, app->camera.y_offset + 5);
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_UP))
		app->camera.y_offset = ft_max(-HEIGHT, app->camera.y_offset - 5);
}
