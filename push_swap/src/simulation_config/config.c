/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:38:34 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 20:38:39 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/simulation_config.h"

t_simulation_config	default_selector_config(void)
{
	t_simulation_config	config;

	config.max_candidates = 30;
	config.cost_threshold_offset = 1;
	config.size_penalty_factor = 10;
	config.heuristic_offset = 1;
	config.heuristic_divisor = 2;
	return (config);
}
