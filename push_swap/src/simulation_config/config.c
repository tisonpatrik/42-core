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