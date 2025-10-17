/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:19 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:33:19 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/grid.h"

void	free_heightmap_info(t_heightmap_info *info)
{
	if (!info)
		return ;
	if (info->fd >= 0)
		close(info->fd);
	free(info);
}

t_heightmap_info	*allocate_heightmap_info(int count_of_rows, int count_of_columns, int fd)
{
	t_heightmap_info	*info;

	if (count_of_rows < 1 || count_of_columns < 1)
		return (NULL);
	
	info = malloc(sizeof(t_heightmap_info));
	if (!info)
		return (NULL);
	info->expected_count_rows = count_of_rows;
	info->expected_count_columns = count_of_columns;
	info->fd = fd;
	return (info);
}
