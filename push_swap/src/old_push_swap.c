/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_push_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:13:20 by ptison            #+#    #+#             */
/*   Updated: 2025/08/18 16:54:29 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <unistd.h>

int	exit_with_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

void	print_array(const int *array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d\n", array[i]);
		i++;
	}
}

// int	*get_input_values(int ac, char **av)
// {
// 	const int		count_of_arguments = ac - 1;
// 	int				*array;
// 	int				i;
// 	t_parse_result	result;

// 	array = (int *)malloc(count_of_arguments * sizeof(*array));
// 	if (array == NULL)
// 		return (NULL);
// 	i = 1;
// 	while (i <= count_of_arguments)
// 	{
// 		result = get_input_number(av[i], array, i - 1);
// 		if (!result.ok)
// 		{
// 			free(array);
// 			return (NULL);
// 		}
// 		array[i - 1] = result.value;
// 		i++;
// 	}
// 	return (array);
// }

// int	main(int ac, char **av)
// {
// 	int	*input;
// 	int	*array;

// 	if (ac < 2)
// 		return (0);
// 	input = get_input_values(ac, av);
// 	if (input == NULL)
// 		return (exit_with_error());
// 	array = indexize_array(input, ac - 1);
// 	print_array(array, ac - 1);
// 	free(input);
// 	return (0);
// }
