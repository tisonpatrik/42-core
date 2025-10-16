/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:25:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 01:16:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/old_app.h"

/* ========================================================================== */
/* FILE READING FUNCTIONS - Pure I/O operations                              */
/* ========================================================================== */

char	**read_map_file_lines_from_fd(int fd, int *line_count)
{
	char	**lines;
	char	*line;
	int		i;
	long	current_pos;

	/* Save current position */
	current_pos = lseek(fd, 0, SEEK_CUR);
	if (current_pos == -1)
		return (NULL);
	
	/* Reset to beginning */
	lseek(fd, 0, SEEK_SET);
	
	/* First pass: count lines */
	*line_count = 0;
	while (ft_get_line(fd) != NULL)
		(*line_count)++;
	
	if (*line_count == 0)
		return (NULL);
	
	/* Reset to beginning for second pass */
	lseek(fd, 0, SEEK_SET);
	
	lines = malloc(sizeof(char *) * (*line_count + 1));
	if (!lines)
		return (NULL);
	
	i = 0;
	while ((line = ft_get_line(fd)) != NULL)
	{
		lines[i] = line;
		i++;
	}
	lines[i] = NULL;
	
	/* Restore original position */
	lseek(fd, current_pos, SEEK_SET);
	return (lines);
}

void	free_map_lines(char **lines)
{
	int	i;

	if (!lines)
		return;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
