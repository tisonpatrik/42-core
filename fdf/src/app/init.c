/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:10:20 by ptison            #+#    #+#             */
/*   Updated: 2025/10/14 00:11:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

t_fdf	*init_fdf(char *filename)
{
	static t_fdf	fdf;

	fdf.view = create_map_from_file(filename);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf.mlx)
	{
		destroy_map(fdf.view);
		handle_error(mlx_strerror(mlx_errno));
	}
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.image)
	{
		destroy_map(fdf.view);
		mlx_close_window(fdf.mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	return (&fdf);
}