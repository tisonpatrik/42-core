/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deg2rad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:35:54 by ptison            #+#    #+#             */
/*   Updated: 2025/10/15 19:36:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_math.h"
/**
 * @brief Converts degrees to radians
 *
 * This function converts an angle from degrees to radians using the formula:
 * radians = degrees * (π / 180)
 *
 * @param degrees The angle in degrees to convert
 * @return The angle in radians
 */
double	ft_deg2rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}
