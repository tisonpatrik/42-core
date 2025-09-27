/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:37:00 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 12:56:23 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		return (EXIT_FAILURE);
	}
	map = get_map(argv[1]);
	map_free(&map);
	return (EXIT_SUCCESS);
}
