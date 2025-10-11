/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/11 17:52:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

void	app_run(t_app app)
{
	mlx_loop_hook(app.mlx, handle_input, &app);
	mlx_close_hook(app.mlx, handle_close, &app);
	mlx_resize_hook(app.mlx, handle_resize, &app);
	mlx_loop(app.mlx);
}