/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:41:28 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 17:49:32 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	input_control(int argc, char *title)
{
	char	*cub_ptr;

	if (argc != 2)
		error_exit("Usage: ./cub3d <path/scene_title.cub>");
	if (ft_strlen(title) < 5)
		error_exit("Scene file format <title.cub>");
	cub_ptr = title + (ft_strlen(title) - CUB_EXTENSION_LEN);
	if (ft_strncmp(cub_ptr, CUB_EXTENSION, CUB_EXTENSION_LEN) != 0)
		error_exit("Scene file format <title.cub>");
}
