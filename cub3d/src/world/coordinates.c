/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:30:34 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:30:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include <math.h>

t_v2i	world_cell(t_v2d position)
{
	return ((t_v2i){(int)floor(position.x), (int)floor(position.y)});
}

t_v2d	world_cell_center(t_v2i map)
{
	t_v2d	center;

	center = ft_v2i_to_v2d(map);
	return (ft_v2d_add(center, (t_v2d){0.5, 0.5}));
}
