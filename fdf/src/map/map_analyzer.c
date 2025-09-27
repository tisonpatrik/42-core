/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:14 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 17:29:53 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

static void	get_count_of_rows(char *trimmed, int *row_count)
{
	char	**tokens;

	tokens = ft_split(trimmed, CHAR_SPACE);
	free(trimmed);
	if (tokens)
	{
		ft_free_array(tokens);
		row_count++;
	}
}

static int	count_file_rows(int fd)
{
	char	*line;
	char	*trimmed;
	char	**tokens;
	int		row_count;

	row_count = 0;
	while ((line = ft_get_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, "\r\n\0");
		free(line);
		if (!trimmed)
			continue ;
		get_count_of_rows(trimmed, &row_count);
	}
	close(fd);
	return (row_count);
}

static int	find_max_row_length(int fd, t_map_info *info)
{
	char	*line;
	char	*trimmed;
	char	**tokens;
	int		token_count;
	int		max_tokens;

	max_tokens = 0;
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
			if (token_count > max_tokens)
				max_tokens = token_count;
			ft_free_array(tokens);
		}
	}
	close(fd);
	info->ncols = max_tokens;
	info->total_cells = info->nrows * info->ncols;
	return (1);
}

t_map_info	*analyze_map_file(const char *file_name)
{
	t_map_info	*info;
	int			row_count;
	int			fd;

	fd = get_file_fd(file_name);
	if (fd < 0)
		return (NULL);
	row_count = count_file_rows(fd);
	if (row_count <= 0)
		return (NULL);
	info = allocate_map_info(row_count);
	if (!info)
		return (NULL);
	if (!find_max_row_length(fd, info))
	{
		free_map_info(info);
		return (NULL);
	}
	return (info);
}
