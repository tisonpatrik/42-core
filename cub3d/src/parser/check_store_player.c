/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_store_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:38:35 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/07 18:47:52 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_store_player(t_map *map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->max_cols)
		{
			if (is_in(map->grid[y][x], PLAYER))
			{
				count++;
				map->p_y = y;
				map->p_x = x;
				map->p_dir = map->grid[y][x];
				map->grid[y][x] = '0';
			}
		}
	}
	if (count != 1)
		return (display_error("Map must have exactly 1 player!"), -1);
	return (0);
}
