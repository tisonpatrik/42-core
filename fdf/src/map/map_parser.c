/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:26 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 17:29:53 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/map.h"


static int	parse_row_tokens(char **tokens, t_map *map, int row_index)
{
	int	value;
	int	col_index;
	int	token_count;

	token_count = count_tokens(tokens);
	
	// Parse actual tokens
	for (int i = 0; tokens[i]; i++)
	{
		value = parse_token(tokens[i]);
		if (value == -1)
			return (0);
		col_index = row_index * map->ncols + i;
		map->cells[col_index].z = value;
		map->cells[col_index].has_color = 0;
		map->cells[col_index].color = 0;
	}
	
	// Fill remaining cells in this row with zeros
	for (int i = token_count; i < map->ncols; i++)
	{
		col_index = row_index * map->ncols + i;
		map->cells[col_index].z = 0;
		map->cells[col_index].has_color = 0;
		map->cells[col_index].color = 0;
	}
	
	return (1);
}

int	parse_map_data(t_map *map, const char *file_name)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	**tokens;
	int		row_index;

	fd = get_file_fd(file_name);
	if (fd < 0)
		return (0);
	
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
		
		if (!parse_row_tokens(tokens, map, row_index))
		{
			ft_free_array(tokens);
			close(fd);
			return (0);
		}
		ft_free_array(tokens);
		row_index++;
	}
	close(fd);
	return (1);
}