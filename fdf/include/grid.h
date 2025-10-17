/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:14:50 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 00:19:16 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERIMENTAL_H
# define EXPERIMENTAL_H

# include "../include/heightmap.h"
# include "../include/camera.h"

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
}				t_point3d;


typedef struct s_grid
{
	t_point3d		**grid3d;
	int				rows;
	int				cols;
	int				high;
	int				low;
	t_arena			*arena;
}					t_grid;

typedef struct s_view
{
	t_camera		camera;
	t_grid			grid;
}					t_view;

t_grid	*allocate_grid(int rows, int cols);
t_grid	*get_grid(t_heightmap *heightmap);
void	free_grid(t_grid *grid);
void	free_wierd_view(t_view *view);
#endif