/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:10:59 by ptison            #+#    #+#             */
/*   Updated: 2025/10/26 11:41:00 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/grid.h"

static bool	handle_grid_row_error(char **tokens, int fd, t_grid *grid)
{
	ft_free_array(tokens);
	close(fd);
	free_grid(grid);
	return (false);
}

static bool	parse_file_content(int fd, t_grid *grid, t_grid_info *info)
{
	char	*line;
	char	**tokens;
	int		row_index;

	line = ft_get_line(fd);
	row_index = 0;
	while (line != NULL)
	{
		tokens = ft_split(line, CHAR_SPACE);
		free(line);
		if (tokens)
		{
			if (!parse_grid_row(tokens, grid, row_index, info))
			{
				return (handle_grid_row_error(tokens, fd, grid));
			}
			ft_free_array(tokens);
			row_index++;
		}
		line = ft_get_line(fd);
	}
	return (true);
}

bool	parse_grid_lines(const char *filename, t_grid *grid, t_grid_info *info)
{
	int	fd;

	fd = get_file_fd(filename);
	if (!parse_file_content(fd, grid, info))
		return (false);
	close(fd);
	return (true);
}
