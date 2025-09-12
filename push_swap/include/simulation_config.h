
#ifndef SIMULATION_CONFIG_H
# define SIMULATION_CONFIG_H



typedef struct s_simulation_config
{
	int	max_candidates;
	int	cost_threshold_offset;
	int	size_penalty_factor;
	int	heuristic_offset;
	int	heuristic_divisor;
}	t_simulation_config;


t_simulation_config	default_selector_config(void);

#endif
