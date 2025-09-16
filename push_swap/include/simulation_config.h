/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_config.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:13:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/16 21:13:20 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_CONFIG_H
# define SIMULATION_CONFIG_H

typedef struct s_simulation_config
{
	int				max_candidates;
	int				cost_threshold_offset;
	int				size_penalty_factor;
	int				heuristic_offset;
	int				heuristic_divisor;
}					t_simulation_config;

t_simulation_config	default_selector_config(void);

#endif
