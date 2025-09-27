/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:14 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 16:43:16 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/map.h"


static int	count_file_rows(const char *file_name)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	**tokens;
	int		row_count;

	fd = get_file_fd(file_name);
	if (fd < 0)
		return (-1);
	
	row_count = 0;
	while ((line = ft_get_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, "\r\n\0");
		free(line);
		if (!trimmed)
			continue ;
		tokens = ft_split(trimmed, CHAR_SPACE);
		free(trimmed);
		if (tokens)
		{
			ft_free_array(tokens);
			row_count++;
		}
	}
	close(fd);
	return (row_count);
}


static int	count_tokens_per_row(const char *file_name, t_map_info *info)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	**tokens;
	int		row_count;
	int		token_count;

	fd = get_file_fd(file_name);
	if (fd < 0)
		return (0);
	
	row_count = 0;
	while ((line = ft_get_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, "\r\n\0");
		free(line);
		if (!trimmed)
			continue ;
		tokens = ft_split(trimmed, CHAR_SPACE);
		free(trimmed);
		if (tokens)
		{
			token_count = count_tokens(tokens);
			info->row_counts[row_count] = token_count;
			info->total_cells += token_count;
			ft_free_array(tokens);
			row_count++;
		}
	}
	close(fd);
	return (1);
}


t_map_info	*analyze_map_file(const char *file_name)
{
	t_map_info	*info;
	int			row_count;

	// Step 1: Count total rows
	row_count = count_file_rows(file_name);
	if (row_count <= 0)
		return (NULL);
	
	// Step 2: Allocate map_info structure
	info = allocate_map_info(row_count);
	if (!info)
		return (NULL);
	
	// Step 3: Count tokens per row
	if (!count_tokens_per_row(file_name, info))
	{
		free_map_info(info);
		return (NULL);
	}
	
	return (info);
}