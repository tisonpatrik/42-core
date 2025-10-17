/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:59:42 by ptison            #+#    #+#             */
/*   Updated: 2025/10/17 23:07:48 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <math.h>
# include <stdlib.h>

# define BACKGROUND			0x22222200

typedef struct s_point2d_temp
{
	int		x;
	int		y;
	int		rgba;
}			t_point2d_temp;

int	get_color(t_point2d_temp current, t_point2d_temp a, t_point2d_temp b);
#endif