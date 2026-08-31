/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:15:40 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 18:15:41 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_len_validate_map(char *line)
{
	int	len;

	len = 0;
	while (line[len])
	{
		if (!is_in(line[len], MAPCHARS))
			return (-1);
		len++;
	}
	return (len);
}

static int	count_dimens_handle_eof_mapchar(t_file *file)
{
	int	i;
	int	len;

	i = file->index;
	file->map.rows = 0;
	file->map.max_cols = 0;
	len = 0;
	while (i < file->line_count && !empty_line(file->lines[i]))
	{
		erase_white_eof(file->lines[i], EOFCHARS);
		len = count_len_validate_map(file->lines[i]);
		if (len == -1)
			return (display_error("Invalid characters in map!"), -1);
		if (len > file->map.max_cols)
			file->map.max_cols = len;
		file->map.rows++;
		i++;
	}
	if (file->map.rows == 0 || file->map.max_cols == 0)
		return (display_error("File has no map!"), -1);
	if (file->map.rows < 3 || file->map.max_cols < 3)
		return (display_error("Map is too small!"), -1);
	return (0);
}

static char	*pad_line_with_spaces(char *line, int len)
{
	char	*padded;
	int		i;

	padded = malloc(sizeof(char) * (len + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (line[i])
	{
		padded[i] = line[i];
		i++;
	}
	while (i < len)
		padded[i++] = ' ';
	padded[i] = '\0';
	return (padded);
}

int	load_map(t_file *file, t_scene_config *cfg)
{
	int	i;
	int	len;

	if (count_dimens_handle_eof_mapchar(file) == -1)
		return (-1);
	file->map.grid = malloc(sizeof(char *) * (file->map.rows + 1));
	if (!file->map.grid)
		return (display_error("Map allocation failed!"), -1);
	i = 0;
	len = file->map.max_cols;
	while (i < file->map.rows)
	{
		file->map.grid[i] = pad_line_with_spaces(file->lines[file->index], len);
		if (!file->map.grid[i])
			error_free_exit("Map line allocation failed!", cfg, file);
		i++;
		file->index++;
	}
	file->map.grid[i] = NULL;
	return (0);
}
