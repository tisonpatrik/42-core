/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:48:27 by ptison            #+#    #+#             */
/*   Updated: 2025/08/16 16:57:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdlib.h>

int	is_valid_input(char *original, int number)
{
	int		len;
	char	*reverse_int;
	int		reverse_len;
	int		ok;

	len = ft_strlen(original);
	if ((number == 0) && (ft_strncmp(original, "0", len) != 0))
	{
		return (0);
	}
	reverse_int = ft_itoa(number);
	reverse_len = ft_strlen(reverse_int);
	ok = (reverse_len == len) && (ft_strncmp(reverse_int, original, len) == 0);
	free(reverse_int);
	if (!ok)
		return (0);
	return (1);
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

int	is_duplicate(t_list *list, int value)
{
	while (list)
	{
		if (*(int *)list->content == value)
			return (1);
		list = list->next;
	}
	return (0);
}

t_list	*get_node(t_list *list, t_list *node, char *str)
{
	int	number;

	number = ft_atoi(str);
	if (!is_valid_input(str, number))
	{
		return (NULL);
	}
	if (is_duplicate(list, number))
	{
		return (NULL);
	}
	node = new_int_node(number);
	return (node);
}
