/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:41:14 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 17:41:15 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_exit(strerror(errno));
	if (read(fd, NULL, 0) < 0)
	{
		close (fd);
		error_exit(strerror(errno));
	}
	return (fd);
}

static int	count_lines(char *file_name)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open_file(file_name);
	line = ft_get_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = ft_get_line(fd);
	}
	close(fd);
	return (count);
}

t_file	init_file(char *file_name, t_scene_config *cfg)
{
	t_file	file;
	int		fd;
	int		i;

	file.index = 0;
	file.map.grid = NULL;
	file.map.rows = 0;
	file.map.max_cols = 0;
	file.map.p_x = 0;
	file.map.p_y = 0;
	file.map.p_dir = 0;
	file.line_count = count_lines(file_name);
	if (file.line_count <= 0)
		error_exit("File is empty!");
	file.lines = ft_calloc((file.line_count + 1), sizeof(char *));
	if (!file.lines)
		error_free_exit("File memory allocation failed!", cfg, &file);
	fd = open_file(file_name);
	i = 0;
	while (i < file.line_count)
		file.lines[i++] = ft_get_line(fd);
	file.lines[i] = NULL;
	ft_get_line(fd);
	close(fd);
	return (file);
}
