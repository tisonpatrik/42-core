/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:16 by ptison            #+#    #+#             */
/*   Updated: 2025/10/19 21:30:38 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/grid.h"

t_grid	*create_grid_from_file(const char *filename, int width, int height)
{
	t_grid_info	info;
	t_grid		*grid;

	info = analyze_grid_file(filename, width, height);
	if (info.rows == 0 || info.cols == 0)
		return (NULL);
	grid = allocate_grid(info.rows, info.cols);
	if (!grid)
		return (NULL);
	if (!parse_grid_lines(filename, grid, &info))
		return (NULL);
	return (grid);
}
