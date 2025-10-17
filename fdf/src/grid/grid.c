/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:32:44 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "../../include/grid.h"



static double	calculate_grid_interval(size_t rows, size_t cols, int width, int height)
{
	double	interval;

	interval = ft_min(width / cols, height / rows) / 2.0;
	return (ft_max(2, interval));
}

void	build_grid_point3d(t_point3d *point, size_t row, int col, int z_value, 
					  t_grid *grid, double interval)
{
	int	x_offset;
	int	y_offset;

	x_offset = (grid->cols - 1) * interval / 2;
	y_offset = (grid->rows - 1) * interval / 2;
	
	point->x = (double)col * interval - x_offset;
	point->y = (double)row * interval - y_offset;
	point->z = (double)z_value * interval;
}

void	build_grid_column_from_tokens(t_heightmap *heightmap, t_grid *grid, size_t row_index, int width, int height)
{
	t_point3d	*point;
	int			col;
	int			z_value;
	int			color;
	size_t		map_index;
	double		interval;

	interval = calculate_grid_interval(grid->rows, grid->cols, width, height);
	
	col = 0;
	while (col < grid->cols)
	{
		map_index = row_index * heightmap->cols + col;
		z_value = heightmap->points[map_index].z;
		point = &(grid->grid3d[row_index][col]);
		
		build_grid_point3d(point, row_index, col, z_value, grid, interval);
		
		grid->high = ft_max(grid->high, point->z);
		grid->low = ft_min(grid->low, point->z);
		
		color = heightmap->points[map_index].color;
		if (color == -1)
			point->mapcolor = 0xFFFFFFFF;
		else
			point->mapcolor = (unsigned int)color;
		
		col++;
	}
}

void	init_grid_defaults(t_grid *grid)
{
	grid->high = INT_MIN;
	grid->low = INT_MAX;
	grid->rows = 0;
	grid->cols = 0;
	grid->grid3d = NULL;
}


t_grid	*get_grid(const char *filename, int width, int height)
{
    size_t row = 0;
	t_heightmap *heightmap = read_heightmap_from_file(filename);
	t_grid *grid = allocate_grid(heightmap->rows, heightmap->cols);
	
	if (!grid)
		return (NULL);

	while (row < heightmap->rows)
    {
		build_grid_column_from_tokens(heightmap, grid, row, width, height);
        row++;
    }
	
	return (grid);
}

