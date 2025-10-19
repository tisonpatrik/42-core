/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:50:28 by ptison            #+#    #+#             */
/*   Updated: 2025/10/19 21:50:31 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

t_renderer	init_renderer(void)
{
	t_renderer	renderer;

	renderer.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	renderer.img = mlx_new_image(renderer.mlx, WIDTH, HEIGHT);
	renderer.width = WIDTH;
	renderer.height = HEIGHT;
	return (renderer);
}
