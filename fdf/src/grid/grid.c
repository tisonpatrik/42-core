/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:52:31 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "../../include/grid.h"

static bool	parse_grid_lines(t_grid_info info, t_grid *grid, int width, int height)
{
	char	*line;
	char	**tokens;
	int		row_index;

	row_index = 0;
	while ((line = ft_get_line(info.fd)) != NULL)
	{
		tokens = ft_split(line, CHAR_SPACE);
		free(line);
		
		if (tokens)
		{
			if (!parse_grid_row(tokens, grid, row_index, width, height))
			{
				ft_free_array(tokens);
				close(info.fd);
				free_grid(grid);
				return (false);
			}
			ft_free_array(tokens);
		}
		row_index++;
	}
	return (true);
}

t_grid	*create_grid_from_file(const char *filename, int width, int height)
{
	t_grid_info	info;
	t_grid		*grid;

	info = analyze_grid_file(filename);
	if (info.fd < 0 || info.rows == 0 || info.cols == 0)
		return (NULL);
	
	grid = allocate_grid(info.rows, info.cols);
	if (!grid)
	{
		close(info.fd);
		return (NULL);
	}
	
	if (!parse_grid_lines(info, grid, width, height))
		return (NULL);
	
	close(info.fd);
	return (grid);
}
