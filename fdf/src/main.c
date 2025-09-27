/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 17:32:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <map_file>\n", 2);
		return (EXIT_FAILURE);
	}
	
	// Load map from file
	map = read_map_from_file(argv[1]);
	if (!map)
	{
		ft_putstr_fd("Error: Failed to load map\n", 2);
		return (EXIT_FAILURE);
	}

	free_map(map);
	return (EXIT_SUCCESS);
}
