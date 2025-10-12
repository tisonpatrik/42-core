/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 22:01:34 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

void	handle_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putendl_fd((char *)message, 2);
	}
	else
		perror("FdF");
	exit(1);
}

void	app_run(t_app *app)
{
	render_image(app);
	if (mlx_image_to_window(app->mlx, app->image, 0, 0) == -1)
	{
		free_map(app->map);
		mlx_close_window(app->mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(app->mlx, &handle_keybinds, app);
	mlx_loop_hook(app->mlx, &handle_rotate, app);
	mlx_loop_hook(app->mlx, &handle_projection, app);
	mlx_scroll_hook(app->mlx, &handle_scroll, app);
	mlx_loop_hook(app->mlx, &render_image, app);
	mlx_loop(app->mlx);
	mlx_terminate(app->mlx);

}