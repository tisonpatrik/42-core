/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:28:48 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 22:03:26 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
#define VIEW_H
# include "types.h"
# include "map.h"
# include <math.h>
# include "render.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"


typedef struct s_view
{
	int			width;
	int			height;
	int			x_offset;
	int			y_offset;
	int			interval;
	float		alpha;
	float		beta;
	float		xrotate;
	float		yrotate;
	float		zrotate;
	float		zoom;
	float		zscale;
}				t_view;


#endif