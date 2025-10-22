/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lod_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:22:56 by ptison            #+#    #+#             */
/*   Updated: 2025/10/23 00:23:27 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

int calculate_lod_step(int rows, int cols, double zoom)
{
	int max_dim = rows > cols ? rows : cols;
	
	// Base LOD based on grid size
	int base_step;
	if (max_dim < 50)
		base_step = 1;
	else if (max_dim < 150)
		base_step = 2;
	else if (max_dim < 300)
		base_step = 3;
	else
		base_step = 4;
	
	// Adjust for zoom - higher zoom = more detail (lower step)
	// At zoom 1.0: use base_step
	// At zoom 2.0: use base_step/2 (more detail)
	// At zoom 0.5: use base_step*2 (less detail)
	int final_step;
	if (zoom >= 2.0)
		final_step = base_step / 2;
	else if (zoom >= 1.0)
		final_step = base_step;
	else if (zoom >= 0.5)
		final_step = base_step * 2;
	else
		final_step = base_step * 4;
	
	// Ensure minimum step of 1
	return final_step < 1 ? 1 : final_step;
}