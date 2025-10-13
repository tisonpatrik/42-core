/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:14:06 by ptison            #+#    #+#             */
/*   Updated: 2025/10/14 00:54:52 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

void	run_app(t_fdf *fdf)
{
	display_menu(fdf->mlx);
	draw_image(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		free_view(fdf->view);
		mlx_close_window(fdf->mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(fdf->mlx, &ft_hook, fdf);
	mlx_loop_hook(fdf->mlx, &ft_hook_rotate, fdf);
	mlx_loop_hook(fdf->mlx, &ft_hook_project, fdf);
	mlx_scroll_hook(fdf->mlx, &fdf_scrollhook, fdf);
	mlx_loop_hook(fdf->mlx, &draw_image, fdf);
	mlx_loop(fdf->mlx);
}