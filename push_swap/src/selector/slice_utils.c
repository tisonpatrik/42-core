/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:40:52 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 21:40:53 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../include/selector.h"

// RemoveElementAt removes an element at the specified index from an array
int	*remove_element_at(int *arr, int size, int index, int *new_size)
{
	int	*result;
	int	i;
	int	j;

	if (index < 0 || index >= size)
	{
		*new_size = size;
		return (NULL);
	}
	result = malloc(sizeof(int) * (size - 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != index)
		{
			result[j] = arr[i];
			j++;
		}
		i++;
	}
	*new_size = size - 1;
	return (result);
}

// InsertElementAt inserts an element at the specified index into an array
int	*insert_element_at(int *arr, int size, int index, int value, int *new_size)
{
	int	*result;
	int	i;

	if (index < 0 || index > size)
	{
		*new_size = size;
		return (NULL);
	}
	result = malloc(sizeof(int) * (size + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < index)
	{
		result[i] = arr[i];
		i++;
	}
	result[i] = value;
	i++;
	while (i <= size)
	{
		result[i] = arr[i - 1];
		i++;
	}
	*new_size = size + 1;
	return (result);
}

// SnapshotStack converts a stack to an array representation for efficient processing
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

// CalculateBreakpoints calculates the number of breakpoints in a cyclic array
int	calculate_breakpoints(int *arr, int size)
{
	int	breakpoints;
	int	i;

	if (is_empty_or_single(arr, size))
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
