/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:10:22 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 22:01:53 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "types.h"
# include <stdlib.h>
# include "../lib/libft/include/libft.h"

typedef struct s_render_grid
{
	int			count_of_rows;
	int			count_of_columns;
	t_point		**points;
}				t_render_grid;

t_render_grid	*grid_alloc(int height, int width);
void			grid_free(t_render_grid *grid);
void			render_image(void *param);
#endif