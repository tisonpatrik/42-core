/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_cfg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:15:56 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 18:15:57 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_map_start(t_file *file, t_scene_config *cfg)
{
	char	*line;
	int		i;

	if (!is_config_complete(cfg))
		return (display_error("Missing textures or rgb!"), 0);
	i = file->index;
	while (file->lines[i] && empty_line(file->lines[i]))
		i++;
	if (!file->lines[i])
		return (display_error("Map is missing!"), 0);
	line = file->lines[i];
	while (*line && is_in(*line, SPACE))
		line++;
	if (!is_in(*line, MAPCHARS))
		return (display_error("Invalid content of file!"), 0);
	return (1);
}

int	is_after_map_empty(t_file *file)
{
	int	i;

	i = file->index;
	while (i < file->line_count)
	{
		if (!empty_line(file->lines[i]))
			return (display_error("After map lines are not empty!"), 0);
		i++;
	}
	return (1);
}

int	parse_scene_cfg(char *file_name, t_scene_config *cfg)
{
	t_file	file;

	init_scene_cfg(cfg);
	file = init_file(file_name, cfg);
	file.index = 0;
	while (file.index < file.line_count)
	{
		if (empty_line(file.lines[file.index]))
		{
			file.index++;
			continue ;
		}
		if (parse_store_config(file.lines[file.index], cfg, &file))
			file.index++;
		else
			break ;
	}
	if (!is_map_start(&file, cfg))
		error_free_exit(NULL, cfg, &file);
	validate_map(&file, cfg);
	if (!is_after_map_empty(&file))
		error_free_exit(NULL, cfg, &file);
	if (fill_rest_cfg(&file.map, cfg) == -1)
		error_free_exit(NULL, cfg, &file);
	return (free_file(&file), 0);
}
