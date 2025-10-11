/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:31:18 by ptison            #+#    #+#             */
/*   Updated: 2025/10/11 17:33:00 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/app.h"


void	set_background(t_app *app)
{
    uint32_t background = get_catppuccin_background();
    
    uint32_t total_pixels = app->image->width * app->image->height;
    for (uint32_t i = 0; i < total_pixels; i++)
        ((uint32_t *)app->image->pixels)[i] = background;

    mlx_image_to_window(app->mlx, app->image, 0, 0);
}