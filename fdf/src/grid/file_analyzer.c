/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:41:17 by ptison            #+#    #+#             */
/*   Updated: 2025/10/19 21:30:38 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/grid.h"

static int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

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

static double	calculate_grid_interval(size_t rows, size_t cols, int width,
		int height)
{
	double	interval;

	interval = ft_min(width / cols, height / rows) / 2.0;
	return (ft_max(2, interval));
}

static t_grid_info	init_grid_info(void)
{
	t_grid_info	info;

	info.rows = 0;
	info.cols = 0;
	info.interval = 0.0;
	info.x_offset = 0;
	info.y_offset = 0;
	return (info);
}

t_grid_info	analyze_grid_file(const char *filename, int width, int height)
{
	t_grid_info	info;
	int			fd;

	info = init_grid_info();
	fd = get_file_fd(filename);
	analyze_file_content(fd, &info);
	close(fd);
	if (info.rows > 0 && info.cols > 0)
	{
		info.interval = calculate_grid_interval(info.rows, info.cols, width,
				height);
		info.x_offset = info.cols * info.interval / 2;
		info.y_offset = info.rows * info.interval / 2;
	}
	return (info);
}
