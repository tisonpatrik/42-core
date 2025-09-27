/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:43:19 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 17:29:53 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/map.h"


void	free_map_info(t_map_info *info)
{
	if (!info)
		return ;
	free(info);
}

t_map_info	*allocate_map_info(int nrows)
{
	t_map_info	*info;

	info = malloc(sizeof(t_map_info));
	if (!info)
		return (NULL);
	info->nrows = nrows;
	info->ncols = 0;  // Will be set later
	info->total_cells = 0;  // Will be calculated as nrows * ncols
	return (info);
}


