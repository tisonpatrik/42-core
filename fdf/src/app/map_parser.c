/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:25:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:26:55 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

/* ========================================================================== */
/* PUBLIC API FUNCTIONS - Clean interface                                    */
/* ========================================================================== */

void	parse_map(int fd, t_view *map)
{
	char	**lines;
	int		line_count;

	/* Read all lines from file */
	lines = read_map_file_lines_from_fd(fd, &line_count);
	if (!lines)
		error_map(fd, map, MALLOC);
	
	/* Get dimensions and validate */
	if (!get_map_dimensions(lines, line_count, map))
	{
		free_map_lines(lines);
		error_map(fd, map, INVALID_MAP);
	}
	
	/* Parse the map data */
	if (!parse_map_from_lines(lines, line_count, map))
	{
		free_map_lines(lines);
		error_map(fd, map, MALLOC);
	}
	
	free_map_lines(lines);
}

void	get_dimensions(int fd, t_view *map)
{
	char	**lines;
	int		line_count;

	lines = read_map_file_lines_from_fd(fd, &line_count);
	if (!lines)
		error_map(fd, map, MALLOC);
	
	if (!get_map_dimensions(lines, line_count, map))
	{
		free_map_lines(lines);
		error_map(fd, map, INVALID_MAP);
	}
	
	free_map_lines(lines);
}

int	get_cols(int fd, t_view *map, char *line)
{
	int	cols;

	cols = get_column_count(line);
	if (cols == 0)
		error_map(fd, map, INVALID_MAP);
	return (cols);
}