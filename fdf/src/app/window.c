/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:13 by ptison            #+#    #+#             */
/*   Updated: 2025/10/11 17:36:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"


void	handle_input(void *param)
{
	t_app	*app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
}

void	handle_resize(int32_t width, int32_t height, void *param)
{
	t_app	*app = (t_app *)param;
	
	app->mlx->width = width;
	app->mlx->height = height;
	
	mlx_delete_image(app->mlx, app->image);
	app->image = mlx_new_image(app->mlx, width, height);
	if (!app->image)
	{
		ft_putstr_fd("Error: Failed to resize image\n", STDERR_FILENO);
		return;
	}
	
	render_map(app);
}

void	handle_close(void *param)
{	
	t_app	*app = (t_app *)param;
	free_app(*app);
	exit(EXIT_SUCCESS);
}