/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:47:30 by ptison            #+#    #+#             */
/*   Updated: 2025/10/13 23:02:21 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/app.h"

void	ft_free_tab(void **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_view *map)
{
	if (!map)
		return ;
	if (map->grid.grid2d)
		ft_free_tab((void **)map->grid.grid2d, map->grid_info.rows);
	if (map->grid.grid3d)
		ft_free_tab((void **)map->grid.grid3d, map->grid_info.rows);
	free(map);
}

void	handle_error(const char *message)
{
	if (errno == 0)
	{
		ft_putstr_fd("FdF: ", 2);
		ft_putendl_fd((char *)message, 2);
	}
	else
		perror("FdF");
	exit(1);
}

void	error_map(int fd, t_view *map, char *message)
{
	close(fd);
	free_map(map);
	handle_error(message);
}
