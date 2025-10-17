/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_factory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:33:44 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 23:50:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/old_app.h"

/* ========================================================================== */
/* VIEW CREATION - Pure view structure management                            */
/* ========================================================================== */

t_view	*create_view(void)
{
	t_view	*view;

	view = malloc(sizeof(t_view));
	if (!view)
		return (NULL);
	
	init_map_defaults(view);
	return (view);
}

/* ========================================================================== */
/* GRID FACTORY - High-level map creation orchestration                     */
/* ========================================================================== */

t_view	*create_map_from_file(const char *filename)
{
	t_view	*view;
	int		fd;

	/* Create view structure */
	view = create_view();
	if (!view)
		return (NULL);
	
	/* Open file and get dimensions */
	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		free(view);
		handle_error(FILE_ERROR);
	}
	
	get_dimensions(fd, view);
	
	/* Allocate grid memory */
	if (!allocate_grid_memory(view))
	{
		free(view);
		handle_error(MALLOC);
	}
	
	/* Calculate camera interval */
	calculate_camera_interval(view);
		
	parse_map_for_view(fd, view);
	close(fd);
	
	/* Set color information */
	set_zcolor(&view->grid);
	return (view);
}

void	destroy_map(t_view *view)
{
	if (!view)
		return;
	
	free_grid_memory(view);
	free(view);
}
