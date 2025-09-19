/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:49:45 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 20:49:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

t_optimizer_config	*create_default_optimizer_config(void)
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

t_optimizer_config	*create_custom_optimizer_config(int max_gap,
		bool enable_merge, bool enable_cancel_pairs, bool enable_cancel_across,
		int max_iterations)
{
	t_optimizer_config	*config;

	config = malloc(sizeof(t_optimizer_config));
	if (!config)
		return (NULL);
	config->max_bubble_gap = max_gap;
	config->enable_merge_neighbors = enable_merge;
	config->enable_cancel_pairs = enable_cancel_pairs;
	config->enable_cancel_across = enable_cancel_across;
	config->max_iterations = max_iterations;
	return (config);
}

void	free_optimizer_config(t_optimizer_config *config)
{
	if (config)
		free(config);
}
