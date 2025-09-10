/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candidate_enumerator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:41:17 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 23:16:16 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

t_candidate	create_candidate_for_node(t_candidate_enumerator *enumerator,
	t_node *node, int node_index, int *bvals, int bvals_size, int size_a)
{
	int			val;
	int			to_idx;
	t_position	position;
	int			base;
	int			penalty;

	val = get_content(node);
	to_idx = find_insertion_index(bvals, bvals_size, val);
	position = calculate_position_cost(enumerator->cost_calc, node_index, 
		to_idx, size_a, bvals_size);
	base = position.total;
	penalty = calculate_penalty(enumerator->cost_calc, bvals, 
		bvals_size, to_idx, val);
	return (new_candidate(position, base + penalty));
}



t_candidate	*allocate_candidates_array(int size)
{
	t_candidate	*candidates;

	candidates = malloc(sizeof(t_candidate) * size);
	return (candidates);
}
void	cleanup_enumerate_resources(t_candidate *candidates, 
	t_candidate *filtered, t_candidate *result)
{
	if (candidates)
		free(candidates);
	if (filtered)
		free(filtered);
	(void)result; // result is returned, not freed here
}

t_candidate_enumerator	*new_candidate_enumerator(t_selector_config config)
{
	t_candidate_enumerator	*enumerator;

	enumerator = malloc(sizeof(t_candidate_enumerator));
	if (!enumerator)
		return (NULL);
	enumerator->cost_calc = new_cost_calculator(config);
	if (!enumerator->cost_calc)
	{
		free(enumerator);
		return (NULL);
	}
	enumerator->config = config;
	return (enumerator);
}

void	free_candidate_enumerator(t_candidate_enumerator *enumerator)
{
	if (enumerator)
	{
		if (enumerator->cost_calc)
			free_cost_calculator(enumerator->cost_calc);
		free(enumerator);
	}
}

t_candidate	*filter_and_select_candidates(t_candidate *candidates, 
	int candidate_count, t_selector_config config, int *result_count)
{
	t_candidate	*filtered;
	t_candidate	*result;
	int			filtered_count;

	filtered = filter_candidates_by_threshold(candidates, candidate_count, 
		config.cost_threshold_offset, &filtered_count);
	if (!filtered)
	{
		*result_count = 0;
		return (NULL);
	}
	result = select_top_k_candidates(filtered, filtered_count, 0, result_count);
	free(filtered);
	return (result);
}

t_candidate	*build_candidates_from_stack_a(t_candidate_enumerator *enumerator, 
	t_stack *a, t_stack *b, int *count)
{
	int			size_a;
	int			*bvals;
	int			bvals_size;
	t_candidate	*candidates;
	t_node		*current;
	int			i;

	if (!enumerator || !a || !b || !count)
		return (NULL);
	size_a = get_size(a);
	if (size_a == 0)
		return (NULL);
	bvals = snapshot_stack(b, &bvals_size);
	if (!bvals)
		return (NULL);
	candidates = allocate_candidates_array(size_a);
	if (!candidates)
	{
		free(bvals);
		return (NULL);
	}
	current = get_head(a);
	i = 0;
	while (current != NULL)
	{
		candidates[i] = create_candidate_for_node(enumerator, current, i, 
			bvals, bvals_size, size_a);
		current = get_next(current);
		i++;
	}
	free(bvals);
	*count = size_a;
	return (candidates);
}


t_candidate	*enumerate_a_to_b(t_candidate_enumerator *enumerator, 
	t_stack *a, t_stack *b, int *count)
{
	t_candidate	*candidates;
	t_candidate	*result;
	int			candidate_count;

	if (!enumerator || !a || !b || !count)
		return (NULL);
	candidates = build_candidates_from_stack_a(enumerator, a, b, &candidate_count);
	if (!candidates)
		return (NULL);
	result = filter_and_select_candidates(candidates, candidate_count, 
		enumerator->config, count);
	cleanup_enumerate_resources(candidates, NULL, result);
	return (result);
}

t_candidate	*enumerate_b_to_a(t_candidate_enumerator *enumerator, 
	int *a, int size_a, int *b, int size_b, int *count)
{
	t_candidate	*candidates;
	int			i;
	int			val;
	int			to_idx;
	int			cost_a;
	int			cost_b;
	int			base;
	t_position	position;

	if (!enumerator || !a || !b || !count)
		return (NULL);
	if (size_b == 0)
	{
		*count = 0;
		return (NULL);
	}
	candidates = malloc(sizeof(t_candidate) * size_b);
	if (!candidates)
		return (NULL);
	i = 0;
	while (i < size_b)
	{
		val = b[i];
		to_idx = find_target_position(a, size_a, val);
		cost_a = signed_cost(to_idx, size_a);
		cost_b = signed_cost(i, size_b);
		base = merged_cost(cost_a, cost_b);
		position.from_index = i;
		position.to_index = to_idx;
		position.cost_a = cost_a;
		position.cost_b = cost_b;
		position.total = base;
		candidates[i] = new_candidate(position, base);
		i++;
	}
	*count = size_b;
	return (candidates);
}


