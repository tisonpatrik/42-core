/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:39:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "../../include/grid.h"



double	calculate_grid_interval(size_t rows, size_t cols, int width, int height)
{
	double	interval;

	interval = ft_min(width / cols, height / rows) / 2.0;
	return (ft_max(2, interval));
}

void	init_grid_defaults(t_grid *grid)
{
	grid->high = INT_MIN;
	grid->low = INT_MAX;
	grid->rows = 0;
	grid->cols = 0;
	grid->grid3d = NULL;
}


t_grid	*create_grid_from_file(const char *filename, int width, int height)
{
	t_grid_info	info;
	t_grid		*grid;
	char		*line;
	char		**tokens;
	int			row_index;

	info = analyze_grid_file(filename);
	if (info.fd < 0 || info.rows == 0 || info.cols == 0)
		return (NULL);
	
	grid = allocate_grid(info.rows, info.cols);
	if (!grid)
	{
		close(info.fd);
		return (NULL);
	}
	
	row_index = 0;
	while ((line = ft_get_line(info.fd)) != NULL)
	{
		tokens = ft_split(line, ' ');
		free(line);
		
		if (tokens)
		{
			if (!parse_grid_row(tokens, grid, row_index, width, height))
			{
				ft_free_array(tokens);
				close(info.fd);
				free_grid(grid);
				return (NULL);
			}
			ft_free_array(tokens);
		}
		row_index++;
	}
	
	close(info.fd);
	return (grid);
}
