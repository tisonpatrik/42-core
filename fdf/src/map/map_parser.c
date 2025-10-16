/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:26 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 01:16:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/heightmap.h"
# include "../../include/old_app.h"

/* Privátní funkce pro parsing barvy z hex stringu do MLX42 ARGB formátu */
static uint32_t	parse_color_to_mlx42(const char *color_str)
{
	uint32_t rgb_color;

	if (!color_str)
		return (0xFF45475A);  /* Default barva #45475A s alpha kanálem pro MLX42 */
	
	/* Přeskoč "0x" prefix pokud existuje */
	if (ft_strncmp(color_str, "0x", 2) == 0 || ft_strncmp(color_str, "0X", 2) == 0)
		rgb_color = hex_to_int(color_str + 2);
	else
		rgb_color = hex_to_int(color_str);
	
	/* Přidej alpha kanál (0xFF = plně neprůhledný) pro MLX42 ARGB formát */
	return ((0xFF << 24) | rgb_color);
}

/* Privátní funkce pro parsing tokenu s barvou ve formátu "číslo,barva" */
static t_token_data	parse_token_with_color(const char *token, char *comma_pos)
{
	t_token_data	data;
	char			*z_str;
	char			*color_str;

	data.z_value = 0;
	data.color = 0xFF45475A;  /* Default barva #45475A s alpha kanálem pro MLX42 */
	
	/* Extrahuj Z hodnotu a barvu */
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

/* Parsuje token ve formátu "číslo" nebo "číslo,barva" */
t_token_data	parse_token(const char *token)
{
	t_token_data	data;
	char			*comma_pos;

	data.z_value = 0;
	data.color = 0xFF45475A;  /* Default barva #45475A s alpha kanálem pro MLX42 */
	
	if (!token || token[0] == '\0')
	{
		data.z_value = -1;
		return (data);
	}
	
	/* Najdi čárku pro oddělení hodnoty a barvy */
	comma_pos = ft_strchr(token, ',');
	if (comma_pos)
	{
		/* Token obsahuje barvu: "číslo,barva" */
		data = parse_token_with_color(token, comma_pos);
	}
	else
	{
		/* Pouze číslo bez barvy */
		data.z_value = ft_atoi(token);
	}
	
	return (data);
}


static bool	parse_row_tokens(char **tokens, t_heightmap *heightmap, int row_index)
{
	t_token_data	data;
	int				col_index;
	int				token_count;
	size_t			i;

	i = 0;
	token_count = count_tokens(tokens);
	while (tokens[i])
	{
		data = parse_token(tokens[i]);
		if (data.z_value == -1)
			return (false);
		col_index = row_index * heightmap->cols + i;
		heightmap->points[col_index].z = data.z_value;
		heightmap->points[col_index].color = data.color;
		i++;
	}
	i = token_count;
	while (i < heightmap->cols)
	{
		col_index = row_index * heightmap->cols + i;
		heightmap->points[col_index].z = 0;
		heightmap->points[col_index].color = 0xFFFFFFFF;  /* Default bílá barva s alpha kanálem pro MLX42 */
		i++;
	}
	return (true);
}

bool	parse_heightmap(t_heightmap *heightmap, int fd)
{
	char	*line;
	char	*trimmed;
	char	**tokens;
	int		row_index;
	row_index = 0;
	while ((line = ft_get_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, "\r\n\0");
		free(line);
		if (!trimmed)
			continue ;
		tokens = ft_split(trimmed, CHAR_SPACE);
		free(trimmed);
		if (!tokens)
			continue ;
		if (!parse_row_tokens(tokens, heightmap, row_index))
		{
			ft_free_array(tokens);
			close(fd);
			return (0);
		}
		ft_free_array(tokens);
		row_index++;
	}
	close(fd);
	return (true);
}
