/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:46:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 10:41:07 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/app.h"

void	hook(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->renderer.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->renderer.mlx);
}
