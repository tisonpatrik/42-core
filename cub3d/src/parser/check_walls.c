#include "parsing.h"

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

// static int check_surrounding(t_map *map, int y, int x)
// {
// 	if (y == 0 || y == map->rows - 1 ||
// 		x == 0 || x == map->max_cols - 1)
// 		return (-1);
// 	if (map->grid[y - 1][x] == ' ' ||
// 		map->grid[y + 1][x] == ' ' ||
// 		map->grid[y][x - 1] == ' ' ||
// 		map->grid[y][x + 1] == ' ')
// 		return (-1);
// 	return (0);
// }

// int check_walls(t_map *map)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < map->rows)
// 	{
// 		x = 0;
// 		while (x < map->max_cols)
// 		{
// 			if (map->grid[y][x] == '0')
// 			{
// 				if (check_surrounding(map, y, x) == -1)
// 					return(display_error("Map is not closed!"), -1);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }
