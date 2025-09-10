/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:40:52 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:49:55 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/selector.h"

int	*snapshot_stack(t_stack *stack, int *size)
{
	int		*result;
	t_node	*current;
	int		i;

	*size = get_size(stack);
	if (*size == 0)
		return (NULL);
	result = malloc(sizeof(int) * *size);
	if (!result)
		return (NULL);
	current = get_tail(stack);
	i = 0;
	while (current != NULL)
	{
		result[i] = get_content(current);
		current = get_prev(current);
		i++;
	}
	return (result);
}

int	calculate_breakpoints(int *arr, int size)
{
	int	breakpoints;
	int	i;

	if (size <= 1)
		return (0);
	breakpoints = 0;
	i = 0;
	while (i < size - 1)
	{
		if (arr[i] > arr[i + 1])
			breakpoints++;
		i++;
	}
	if (arr[size - 1] > arr[0])
		breakpoints++;
	return (breakpoints);
}
