/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:25:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/14 00:50:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

/* ========================================================================== */
/* PUBLIC API FUNCTIONS - Clean interface                                    */
/* ========================================================================== */

void	parse_map_for_view(int fd, t_view *view)
{
	char	**lines;
	int		line_count;

	/* Read all lines from file */
	lines = read_map_file_lines_from_fd(fd, &line_count);
	if (!lines)
		error_map(fd, view, MALLOC);
	
	/* Get dimensions and validate */
	if (!get_map_dimensions(lines, line_count, view))
	{
		free_map_lines(lines);
		error_map(fd, view, INVALID_MAP);
	}
	
	/* Parse the map data */
	if (!parse_map_from_lines(lines, line_count, view))
	{
		free_map_lines(lines);
		error_map(fd, view, MALLOC);
	}
	
	free_map_lines(lines);
}

void	get_dimensions(int fd, t_view *view)
{
	char	**lines;
	int		line_count;

	lines = read_map_file_lines_from_fd(fd, &line_count);
	if (!lines)
		error_map(fd, view, MALLOC);
	
	if (!get_map_dimensions(lines, line_count, view))
	{
		free_map_lines(lines);
		error_map(fd, view, INVALID_MAP);
	}
	
	free_map_lines(lines);
}

