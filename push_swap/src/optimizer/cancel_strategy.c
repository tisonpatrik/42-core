#include "../../include/optimizer.h"

static bool	cancel_strategy_can_apply(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 2)
		return (false);
	return (true);
}

static t_list	*cancel_strategy_apply(t_list *src, t_optimizer_arena *arena, bool *changed)
{
	t_list	*result;
	bool	has_changed = false;

	if (!src || !arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	// Run all three cancellation functions in sequence, just like the original
	result = cancel_inverse_pairs(src, &has_changed);
	if (result)
	{
		replace_sequence_if_changed(&src, result, has_changed, &has_changed);
	}
	
	result = cancel_across_other_stack_a(src, &has_changed);
	if (result)
	{
		replace_sequence_if_changed(&src, result, has_changed, &has_changed);
	}
	
	result = cancel_across_other_stack_b(src, &has_changed);
	if (changed)
		*changed = has_changed;
	return (result);
}

t_optimization_strategy	*create_cancel_strategy(void)
{
	static t_optimization_strategy	strategy = {
		.name = "cancel",
		.can_apply = cancel_strategy_can_apply,
		.apply = cancel_strategy_apply,
		.priority = 3
	};
	return (&strategy);
}
