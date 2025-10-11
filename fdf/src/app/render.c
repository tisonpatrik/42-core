/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:09:04 by ptison            #+#    #+#              */
/*   Updated: 2025/10/11 17:35:00 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

void	render_map(t_app *app)
{
	// Display the image (only once during initialization)
	mlx_image_to_window(app->mlx, app->image, 0, 0);
}
