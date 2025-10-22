/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:38:49 by ptison            #+#    #+#             */
/*   Updated: 2025/10/22 23:19:23 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/grid.h"

static uint32_t	parse_color_to_mlx42(const char *color_str)
{
	uint32_t	rgb_color;

	if (!color_str)
		return (TEXT_COLOR);
	if (ft_strncmp(color_str, "0x", 2) == 0 || ft_strncmp(color_str, "0X",
			2) == 0)
		rgb_color = hex_to_int(color_str + 2);
	else
		rgb_color = hex_to_int(color_str);
	return ((rgb_color << 8) | 0xFF);
}

static t_token_data	parse_token_with_color(const char *token, char *comma_pos)
{
	t_token_data	data;
	char			*z_str;
	char			*color_str;

	data.z_value = 0;
	data.color = 0xFF45475A;
	data.success = true;
	z_str = ft_substr(token, 0, comma_pos - token);
	color_str = ft_strdup(comma_pos + 1);
	if (z_str)
	{
		data.z_value = ft_atoi(z_str);
		free(z_str);
	}
	if (color_str)
	{
		data.color = parse_color_to_mlx42(color_str);
		free(color_str);
	}
	return (data);
}

t_token_data	parse_token(const char *token)
{
	t_token_data	data;
	char			*comma_pos;

	data.z_value = 0;
	data.color = TEXT_COLOR;
	data.success = true;
	if (!token || token[0] == '\0')
	{
		data.success = false;
		return (data);
	}
	comma_pos = ft_strchr(token, ',');
	if (comma_pos)
		data = parse_token_with_color(token, comma_pos);
	else
		data.z_value = ft_atoi(token);
	return (data);
}
