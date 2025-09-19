/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:45 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 21:50:21 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_optimizer_config	*create_optimizer_config(void)
{
	t_optimizer_config	*config;

	config = malloc(sizeof(t_optimizer_config));
	if (!config)
		return (NULL);
	config->max_bubble_gap = 4;
	config->enable_merge_neighbors = true;
	config->enable_cancel_pairs = true;
	config->enable_cancel_across = true;
	config->max_iterations = 100;
	return (config);
}


void	free_optimizer_config(t_optimizer_config *config)
{
	if (config)
		free(config);
}
