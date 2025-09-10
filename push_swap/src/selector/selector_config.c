/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:13:57 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:14:13 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/selector.h"

t_selector_config	default_selector_config(void)
{
	t_selector_config	config;

	config.max_candidates = 30;
	config.cost_threshold_offset = 1;
	config.size_penalty_factor = 10;
	config.heuristic_offset = 1;
	config.heuristic_divisor = 2;
	return (config);
}
