/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:19:07 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 18:22:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

static t_arena	*create_render_arena(int rows, int cols)
{
	size_t	total_size;

	total_size = sizeof(t_point2d) * rows * cols;
	return (ft_arena_create(total_size));
}

static t_render_grid	setup_render_grid(t_arena *arena, int rows, int cols)
{
	t_render_grid	render_grid;

	render_grid.points = ft_arena_alloc(arena, sizeof(t_point2d) * rows * cols);
	if (!render_grid.points)
	{
		ft_arena_destroy(arena);
		render_grid.rows = 0;
		render_grid.cols = 0;
		render_grid.arena = NULL;
		return (render_grid);
	}
	render_grid.rows = rows;
	render_grid.cols = cols;
	render_grid.arena = arena;
	return (render_grid);
}

t_render_grid	allocate_render_grid(int rows, int cols)
{
	t_render_grid	render_grid;
	t_arena			*arena;

	arena = create_render_arena(rows, cols);
	if (!arena)
	{
		render_grid.points = NULL;
		render_grid.rows = 0;
		render_grid.cols = 0;
		render_grid.arena = NULL;
		return (render_grid);
	}
	return (setup_render_grid(arena, rows, cols));
}

void	free_render_grid(t_render_grid *render_grid)
{
	if (!render_grid || !render_grid->arena)
		return ;
	ft_arena_destroy(render_grid->arena);
	render_grid->points = NULL;
	render_grid->rows = 0;
	render_grid->cols = 0;
	render_grid->arena = NULL;
}