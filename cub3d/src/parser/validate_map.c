/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:16:30 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 18:16:37 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	validate_map(t_file *file, t_scene_config *cfg)
{
	if (load_map(file, cfg) == -1)
		error_free_exit(NULL, cfg, file);
	if (check_store_player(&file->map) == -1)
		error_free_exit(NULL, cfg, file);
	if (check_walls(&file->map) == -1)
		error_free_exit(NULL, cfg, file);
	return (0);
}
