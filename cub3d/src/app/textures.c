/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:28:23 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:28:23 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rom.h"
#include "io.h"
#include "parser.h"

bool	texture_load_png(mlx_texture_t **destination, const char *path,
	const char *name)
{
	*destination = mlx_load_png(path);
	if (*destination)
		return (true);
	ft_putstr_fd("Error\nFailed to load ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(mlx_strerror(mlx_errno), 2);
	return (false);
}

static bool	load_wall_textures(t_texture_set *textures,
	const t_wall_paths *paths)
{
	return (texture_load_png(&textures->wall[TEX_NORTH], paths->north, "NO")
		&& texture_load_png(&textures->wall[TEX_SOUTH], paths->south, "SO")
		&& texture_load_png(&textures->wall[TEX_WEST], paths->west, "WE")
		&& texture_load_png(&textures->wall[TEX_EAST], paths->east, "EA"));
}

int	textures_load(t_texture_set *textures, const t_scene_config *config,
	bool bonus_enabled)
{
	if (!load_wall_textures(textures, &config->wall_paths))
		return (EXIT_FAILURE);
	if (!bonus_enabled)
		return (EXIT_SUCCESS);
	if (!textures_load_bonus(textures))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	textures_cleanup(t_texture_set *textures)
{
	int	i;

	i = 0;
	while (i < TEX_WALL_COUNT)
	{
		if (textures->wall[i])
			mlx_delete_texture(textures->wall[i]);
		textures->wall[i] = NULL;
		i++;
	}
	if (textures->fire)
		mlx_delete_texture(textures->fire);
	if (textures->scorch)
		mlx_delete_texture(textures->scorch);
	if (textures->orb)
		mlx_delete_texture(textures->orb);
	textures->fire = NULL;
	textures->scorch = NULL;
	textures->orb = NULL;
}
