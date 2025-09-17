#include "../../include/optimizer.h"

static bool	bubble_strategy_can_apply(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 3)
		return (false);
	return (true);
}

static t_list	*bubble_strategy_apply(t_list *src, t_optimizer_arena *arena, bool *changed)
{
	t_optimizer_config	*config;
	t_list				*result;

	if (!src || !arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	config = create_default_optimizer_config();
	if (!config)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	result = bubble_across_other_stack(src, config->max_bubble_gap, changed);
	free_optimizer_config(config);
	return (result);
}

t_optimization_strategy	*create_bubble_strategy(void)
{
	static t_optimization_strategy	strategy = {
		.name = "bubble",
		.can_apply = bubble_strategy_can_apply,
		.apply = bubble_strategy_apply,
		.priority = 1
	};
	return (&strategy);
}
