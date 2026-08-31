/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_store_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:16:01 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/07 19:17:17 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_config_complete(t_scene_config *cfg)
{
	return (cfg->wall_paths.north && cfg->wall_paths.south
		&& cfg->wall_paths.west && cfg->wall_paths.east
		&& cfg->ceiling_color.alpha == FT_COLOR_CHANNEL_MAX
		&& cfg->floor_color.alpha == FT_COLOR_CHANNEL_MAX);
}

static int	handle_identifier(char *line, t_scene_config *cfg)
{
	if (!ft_strncmp("NO", line, 2) && is_in(*(line + 2), SPACE))
		return (parse_texture((line + 2), &cfg->wall_paths.north, 'n'));
	else if (!ft_strncmp("SO", line, 2) && is_in(*(line + 2), SPACE))
		return (parse_texture((line + 2), &cfg->wall_paths.south, 's'));
	else if (!ft_strncmp("WE", line, 2) && is_in(*(line + 2), SPACE))
		return (parse_texture((line + 2), &cfg->wall_paths.west, 'w'));
	else if (!ft_strncmp("EA", line, 2) && is_in(*(line + 2), SPACE))
		return (parse_texture((line + 2), &cfg->wall_paths.east, 'e'));
	else if (*line == 'F' && is_in(*(line + 1), SPACE))
		return (parse_rgb((line + 1), &cfg->floor_color, 'f', cfg));
	else if (*line == 'C' && is_in(*(line + 1), SPACE))
		return (parse_rgb((line + 1), &cfg->ceiling_color, 'c', cfg));
	if (is_in(*line, MAPCHARS))
	{
		if (is_map_line(line))
			return (-2);
	}
	return (-1);
}

static int	is_texture_path(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	validate_texture_path(t_scene_config *cfg)
{
	if (!is_texture_path(cfg->wall_paths.north))
		return (display_error("Cannot open NO texture file!"), -1);
	else if (!is_texture_path(cfg->wall_paths.south))
		return (display_error("Cannot open SO texture file!"), -1);
	else if (!is_texture_path(cfg->wall_paths.east))
		return (display_error("Cannot open EA texture file!"), -1);
	else if (!is_texture_path(cfg->wall_paths.west))
		return (display_error("Cannot open WE texture file!"), -1);
	return (0);
}

int	parse_store_config(char *line, t_scene_config *cfg, t_file *file)
{
	int	status;

	status = 0;
	while (*line && is_in(*line, WHITE))
		line++;
	status = handle_identifier(line, cfg);
	if (status == 1)
		error_free_exit(NULL, cfg, file);
	if (status == -2)
	{
		if (!is_config_complete(cfg))
		{
			if (is_in(*line, TEXRGBSTART))
				error_free_exit("Invalid line format in tex/rgb section!",
					cfg, file);
			error_free_exit("Missing texture or rgb!", cfg, file);
		}
		if (check_duplicates(cfg) == -1 || validate_texture_path(cfg) == -1)
			error_free_exit(NULL, cfg, file);
		return (0);
	}
	if (status == -1)
		error_free_exit("Invalid line format in tex/rgb section!", cfg, file);
	return (1);
}
