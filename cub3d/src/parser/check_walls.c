/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:40:09 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/10 13:26:30 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	get_cell(char **grid, int y, int x, t_map *map)
{
	if (y < 0 || y >= map->rows || x < 0 || x >= map->max_cols)
		return (' ');
	if (!grid[y])
		return (' ');
	return (grid[y][x]);
}

static int	check_surrounding(char **grid, int y, int x, t_map *map)
{
	if (get_cell(grid, y - 1, x, map) == ' '
		|| get_cell(grid, y + 1, x, map) == ' '
		|| get_cell(grid, y, x - 1, map) == ' '
		|| get_cell(grid, y, x + 1, map) == ' ')
		return (-1);
	if (get_cell(grid, y - 1, x - 1, map) == ' '
		|| get_cell(grid, y - 1, x + 1, map) == ' '
		|| get_cell(grid, y + 1, x - 1, map) == ' '
		|| get_cell(grid, y + 1, x + 1, map) == ' ')
		return (-1);
	return (0);
}

int	check_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->max_cols && map->grid[y][x])
		{
			if (map->grid[y][x] == '0')
			{
				if (check_surrounding(map->grid, y, x, map) == -1)
				{
					display_error("Map is not closed!");
					return (-1);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}
