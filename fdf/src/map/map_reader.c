/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:45:10 by ptison            #+#    #+#             */
/*   Updated: 2025/10/16 21:25:55 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/heightmap.h"

t_heightmap	*read_heightmap_from_file(const char *file_name)
{
	t_heightmap		*heightmap;
	t_heightmap_info	*info;
	int			fd;

	info = analyze_heightmap_file(file_name);
	if (!info)
		return (NULL);
	heightmap = allocate_heightmap(info);
	if (!heightmap)
	{
		free_heightmap_info(info);
		return (NULL);
	}
	fd = get_file_fd(file_name);
	if (fd < 0)
	{
		ft_arena_destroy(heightmap->arena);
		free(heightmap);
		free_heightmap_info(info);
		return (NULL);
	}
	if (!parse_heightmap(heightmap, fd))
	{
		close(fd);
		ft_arena_destroy(heightmap->arena);
		free(heightmap);
		free_heightmap_info(info);
		return (NULL);
	}
	close(fd);
	free_heightmap_info(info);
	return (heightmap);
}
