/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:00:00 by ptison            #+#    #+#             */
/*   Updated: 2025/10/12 20:08:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

// Basic point structure
typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}				t_point;

// Color structure
typedef struct s_color
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}				t_color;

#endif
