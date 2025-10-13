/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:25:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:25:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

/* ========================================================================== */
/* DATA STRUCTURE BUILDING FUNCTIONS - Pure data transformation             */
/* ========================================================================== */

void	build_point3d(t_point3d *point, int row, int col, int z_value, 
					  t_view *map)
{
	int	x_offset;
	int	y_offset;

	x_offset = (map->grid.cols - 1) * map->camera.interval / 2;
	y_offset = (map->grid.rows - 1) * map->camera.interval / 2;
	
	point->x = (double)col * map->camera.interval - x_offset;
	point->y = (double)row * map->camera.interval - y_offset;
	point->z = (double)z_value * map->camera.interval;
}

void	build_column_from_tokens(char **tokens, t_view *map, int row)
{
	t_point3d	*point;
	int			col;
	int			z_value;
	int			color;

	col = 0;
	while (col < map->grid.cols && tokens[col])
	{
		z_value = ft_atoi(tokens[col]);
		point = &(map->grid.grid3d[row][col]);
		
		build_point3d(point, row, col, z_value, map);
		
		map->grid.high = ft_max(map->grid.high, point->z);
		map->grid.low = ft_min(map->grid.low, point->z);
		
		color = parse_color_from_token(tokens[col]);
		point->mapcolor = (color == -1) ? 0xFFFFFFFF : (unsigned int)color;
		
		col++;
	}
}
