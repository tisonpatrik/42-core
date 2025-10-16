/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:14 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 20:12:38 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/map.h"

static bool	analyze_line(char *line, int *max_columns)
{
	char	*trimmed;
	char	**tokens;
	int		token_count;

	trimmed = ft_strtrim(line, "\r\n\0");
	if (!trimmed)
		return (false);
	
	tokens = ft_split(trimmed, CHAR_SPACE);
	free(trimmed);
	if (!tokens)
		return (false);
	
	token_count = count_tokens(tokens);
	if (token_count > *max_columns)
		*max_columns = token_count;
	ft_free_array(tokens);
	return (true);
}

t_map_info	*analyze_map_file(const char *file_name)
{
	t_map_info	*info;
	int			fd;
	char		*line;
	int			count_rows;
	int			max_columns;

	fd = get_file_fd(file_name);
	if (fd < 0)
		return (NULL);

	count_rows = 0;
	max_columns = 0;
	while ((line = ft_get_line(fd)) != NULL)
	{
		if (analyze_line(line, &max_columns))
			count_rows++;
		free(line);
	}
	close(fd);

	info = allocate_map_info(count_rows, max_columns, fd);
	if (!info)
		return (NULL);
	return (info);
}
