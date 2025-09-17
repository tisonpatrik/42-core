#include "../../include/optimizer.h"

static bool	merge_strategy_can_apply(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 2)
		return (false);
	return (true);
}

static t_list	*merge_strategy_apply(t_list *src, t_optimizer_arena *arena, bool *changed)
{
	if (!src || !arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	return (merge_neighbors(src, changed));
}

t_optimization_strategy	*create_merge_strategy(void)
{
	static t_optimization_strategy	strategy = {
		.name = "merge",
		.can_apply = merge_strategy_can_apply,
		.apply = merge_strategy_apply,
		.priority = 2
	};
	return (&strategy);
}
