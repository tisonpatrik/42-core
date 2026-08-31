/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 19:16:56 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/07 19:42:30 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_same_texture(char *s1, char *s2)
{
	int	lens1;
	int	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (lens1 != lens2)
		return (0);
	return (ft_strncmp(s1, s2, lens1 + 1) == 0);
}

static int	are_textures_unique(t_scene_config *cfg)
{
	char	*n;
	char	*s;
	char	*e;
	char	*w;

	n = cfg->wall_paths.north;
	s = cfg->wall_paths.south;
	e = cfg->wall_paths.east;
	w = cfg->wall_paths.west;
	if (is_same_texture(n, s) || is_same_texture(n, e) || is_same_texture(n, w)
		|| is_same_texture(s, e) || is_same_texture(s, w)
		|| is_same_texture(e, w))
		return (0);
	return (1);
}

static int	are_color_identical(t_rgba f, t_rgba c)
{
	return (f.red == c.red
		&& f.green == c.green
		&& f.blue == c.blue
		&& f.alpha == c.alpha);
}

int	check_duplicates(t_scene_config *cfg)
{
	if (!are_textures_unique(cfg))
		return (display_error("Textures are not unique!"), -1);
	if (are_color_identical(cfg->floor_color, cfg->ceiling_color))
		return (display_error("Rgb`s are identical!"), -1);
	return (0);
}
