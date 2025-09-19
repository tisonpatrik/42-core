/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_implementations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:48:37 by ptison            #+#    #+#             */
/*   Updated: 2025/09/19 22:12:32 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/optimizer.h"

static bool	bubble_strategy_can_apply(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 3)
		return (false);
	return (true);
}

static t_list	*bubble_strategy_apply(t_list *src, t_optimizer_arena *arena,
		bool *changed)
{
	t_optimizer_config	*config;
	t_list				*result;

	if (!src || !arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	config = create_optimizer_config();
	if (!config)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
	result = bubble_across_other_stack(src, changed);
	free_optimizer_config(config);
	return (result);
}

t_optimization_strategy	*create_bubble_strategy(void)
{
	static t_optimization_strategy	strategy = {.name = "bubble",
			.can_apply = bubble_strategy_can_apply,
			.apply = bubble_strategy_apply, .priority = 1};

	return (&strategy);
}

static bool	merge_strategy_can_apply(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 2)
		return (false);
	return (true);
}

static t_list	*merge_strategy_apply(t_list *src, t_optimizer_arena *arena,
		bool *changed)
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
	static t_optimization_strategy	strategy = {.name = "merge",
			.can_apply = merge_strategy_can_apply,
			.apply = merge_strategy_apply, .priority = 2};

	return (&strategy);
}

static bool	cancel_strategy_can_apply(t_list *seq)
{
	if (!seq || ft_lstsize(seq) < 2)
		return (false);
	return (true);
}

static t_list	*cancel_strategy_apply(t_list *src, t_optimizer_arena *arena,
		bool *changed)
{
	t_list	*result;
	bool	has_changed;

	has_changed = false;
	if (!src || !arena)
	{
		if (changed)
			*changed = false;
		return (NULL);
	}
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
	static t_optimization_strategy	strategy = {.name = "cancel",
			.can_apply = cancel_strategy_can_apply,
			.apply = cancel_strategy_apply, .priority = 3};

	return (&strategy);
}
