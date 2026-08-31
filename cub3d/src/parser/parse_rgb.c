/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:15:49 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 18:15:50 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_rgb_str(char *line)
{
	int	comma_count;

	if (!line || !*line)
		return (0);
	comma_count = 0;
	while (*line && is_in(*line, SPACE))
		line++;
	if (!ft_isdigit(*line))
		return (0);
	while (*line && *line != '\n' && *line != '\r')
	{
		if (*line == ',')
			comma_count++;
		else if (!ft_isdigit(*line) && !is_in(*line, SPACE))
			return (0);
		line++;
	}
	return (comma_count == 2);
}

static int	get_num(char **str)
{
	int	num;

	num = 0;
	while (**str && is_in(**str, SPACE))
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	while (**str && ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		if (num > 255)
			return (-1);
		(*str)++;
	}
	while (**str && is_in(**str, SPACE))
		(*str)++;
	return (num);
}

static long	get_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	r = get_num(&line);
	if (r == -1 || *line != ',')
		return (-1);
	line++;
	g = get_num(&line);
	if (g == -1 || *line != ',')
		return (-1);
	line++;
	b = get_num(&line);
	if (b == -1)
		return (-1);
	while (*line && is_in(*line, WHITE))
		line++;
	if (*line != '\0')
		return (-1);
	return (r << 16 | g << 8 | b);
}

int	parse_rgb(char *line, t_rgba *rgb, char c, t_scene_config *cfg)
{
	long	val;

	while (*line && is_in(*line, SPACE))
		line++;
	if (*line == '\t')
		return (display_error("Tabs are not allowed in rgb!"), 1);
	if (c == 'c' && cfg->ceiling_color.alpha == FT_COLOR_CHANNEL_MAX)
		return (display_error("Ceiling rgb duplicate found!"), 1);
	if (c == 'f' && cfg->floor_color.alpha == FT_COLOR_CHANNEL_MAX)
		return (display_error("Floor rgb duplicate found!"), 1);
	if (!check_rgb_str(line))
		return (display_error("Invalid rgb format!"), 1);
	val = get_rgb(line);
	if (c == 'c' && val == -1)
		return (display_error("Invalid ceiling rgb format!"), 1);
	if (c == 'f' && val == -1)
		return (display_error("Invalid floor rgb format!"), 1);
	*rgb = ft_rgba_create((uint8_t)(val >> 16), (uint8_t)(val >> 8),
			(uint8_t)val, FT_COLOR_CHANNEL_MAX);
	return (0);
}
