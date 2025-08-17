/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:48:27 by ptison            #+#    #+#             */
/*   Updated: 2025/08/17 18:10:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <limits.h>
#include <stdlib.h>

int	is_valid_input(char *original, int number)
{
	int		len;
	char	*normal;
	int		normal_len;
	int		ok;

	len = ft_strlen(original);
	if (number == 0)
		return (len == 1 && original[0] == '0');
	normal = ft_itoa(number);
	if (!normal)
		return (0);
	normal_len = ft_strlen(normal);
	ok = (normal_len == len) && (ft_strncmp(normal, original, len) == 0);
	free(normal);
	return (ok);
}

t_list	*new_int_node(int number)
{
	int		*value;
	t_list	*node;

	value = malloc(sizeof * value);
	if (!value)
		return (NULL);
	*value = number;
	node = ft_lstnew(value);
	if (!node)
	{
		free(value);
		return (NULL);
	}
	return (node);
}

int	is_duplicate(const int *array, int used_len, int value)
{
	int	i;

	i = 0;
	while (i < used_len)
	{
		if (array[i] == value)
			return (1);
		i++;
	}
	return (0);
}

t_parse_result	get_input_number(char *str, const int *array, int used_len)
{
	t_parse_result	result;
	int				number;

	number = ft_atoi(str);
	if (!is_valid_input(str, number))
	{
		result.ok = 0;
		return (result);
	}
	if (is_duplicate(array, used_len, number))
	{
		result.ok = 0;
		return (result);
	}
	result.value = number;
	result.ok = 1;
	return (result);
}
