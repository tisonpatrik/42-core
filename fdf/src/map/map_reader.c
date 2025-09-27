/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:10 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 20:59:16 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map.h"

t_map	*read_map_from_file(const char *file_name)
{
	t_map		*map;
	t_map_info	*info;

	info = analyze_map_file(file_name);
	if (!info)
		return (NULL);
	map = alocate_map(info);
	if (!map)
	{
		free_map_info(info);
		return (NULL);
	}
	if (!parse_map(map, info->fd))
	{
		ft_arena_destroy(map->arena);
		free(map);
		free_map_info(info);
		return (NULL);
	}
	free_map_info(info);
	return (map);
}
