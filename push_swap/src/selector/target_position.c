#include "../../include/selector.h"

static int	find_smallest_greater_than(int *array, int array_size, int target_value)
{
	int	best_idx;
	int	best_val;
	int	i;

	best_idx = -1;
	best_val = 0;
	i = 0;
	while (i < array_size)
	{
		if (array[i] > target_value)
		{
			if (best_idx == -1 || array[i] < best_val)
			{
				best_val = array[i];
				best_idx = i;
			}
		}
		i++;
	}
	return (best_idx);
}

static int	find_minimum_index(int *array, int array_size)
{
	int	min_idx;
	int	min_val;
	int	i;

	min_idx = 0;
	min_val = array[0];
	i = 1;
	while (i < array_size)
	{
		if (array[i] < min_val)
		{
			min_val = array[i];
			min_idx = i;
		}
		i++;
	}
	return (min_idx);
}

int	find_target_position(int *array, int array_size, int target_value)
{
	int	best_idx;

	if (array_size == 0)
		return (0);
	best_idx = find_smallest_greater_than(array, array_size, target_value);
	if (best_idx != -1)
		return (best_idx);
	return (find_minimum_index(array, array_size));
}
