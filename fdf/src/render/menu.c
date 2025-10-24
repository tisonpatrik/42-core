/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:52:21 by ptison            #+#    #+#             */
/*   Updated: 2025/10/24 09:32:45 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/renderer.h"

void	display_menu(mlx_t *mlx)
{
	int	x;
	int	y;

	x = 20;
	y = 20;
	mlx_put_string(mlx, "CONTROLS", x, y);
	mlx_put_string(mlx, "Translate\t\t\t\t\tarrow keys", x, y += 35);
	mlx_put_string(mlx, "Exit\t\t\t\t\t\t\t\t\t\tESC", x, y += 30);
}
