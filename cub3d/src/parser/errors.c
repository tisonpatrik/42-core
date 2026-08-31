/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakrajic <jakrajic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:40:17 by jakrajic          #+#    #+#             */
/*   Updated: 2026/08/06 17:40:18 by jakrajic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	display_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
}

void	error_free_exit(char *msg, t_scene_config *cfg, t_file *file)
{
	if (msg != NULL)
		display_error(msg);
	if (cfg)
		free_scene_cfg(cfg);
	if (file)
		free_file(file);
	exit(EXIT_FAILURE);
}

void	error_exit(char *msg)
{
	display_error(msg);
	exit(EXIT_FAILURE);
}
