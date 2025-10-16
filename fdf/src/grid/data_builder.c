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

# include "../../include/old_app.h"

void	build_point3d(t_point3d *point, int row, int col, int z_value, 
					  t_grid *grid, t_camera *camera)
{
	int	x_offset;
	int	y_offset;

	x_offset = (grid->cols - 1) * camera->interval / 2;
	y_offset = (grid->rows - 1) * camera->interval / 2;
	
	point->x = (double)col * camera->interval - x_offset;
	point->y = (double)row * camera->interval - y_offset;
	point->z = (double)z_value * camera->interval;
}

void	build_column_from_tokens(char **tokens, t_grid *grid, t_camera *camera, int row_intex)
{
	t_point3d	*point;
	int			col;
	int			z_value;
	int			color;

	col = 0;
	while (col < grid->cols && tokens[col])
	{
		z_value = ft_atoi(tokens[col]);
		point = &(grid->grid3d[row_intex][col]);
		
		build_point3d(point, row_intex, col, z_value, grid, camera);
		
		grid->high = ft_max(grid->high, point->z);
		grid->low = ft_min(grid->low, point->z);
		
		color = parse_color_from_token(tokens[col]);
		point->mapcolor = (color == -1) ? 0xFFFFFFFF : (unsigned int)color;
		
		col++;
	}
}
