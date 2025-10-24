/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:40:11 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 10:43:10 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"

t_camera	init_camera_defaults(void)
{
	t_camera	camera;

	camera.interval = 1.0;
	return (camera);
}
