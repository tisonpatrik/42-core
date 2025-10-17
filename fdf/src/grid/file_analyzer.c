/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:41:17 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 01:43:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/grid.h"

static void	analyze_file_content(int fd, t_grid_info *info)
{
	char	*line;
	char	**tokens;

	while ((line = ft_get_line(fd)) != NULL)
	{
		tokens = ft_split(line, CHAR_SPACE);
		free(line);
		
		if (tokens)
		{
			info->cols = ft_max(info->cols, count_tokens(tokens));
			ft_free_array(tokens);
		}
		info->rows++;
	}
}

t_grid_info	analyze_grid_file(const char *filename)
{
	t_grid_info	info;
	int			fd;

	info = init_grid_info();
	
	fd = get_file_fd(filename);
	analyze_file_content(fd, &info);
	close(fd);
	return (info);
}