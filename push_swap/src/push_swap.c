/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:16:34 by ptison            #+#    #+#             */
/*   Updated: 2025/08/16 13:26:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	exit_with_error(void)
{
	fprintf(stderr, "Error\n");
	return (-1);
}

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

	value = malloc(sizeof *value);
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

t_list	*get_input_values(char **ag)
{
	t_list	*list;
	int		i;
	int		number;
	t_list	*node;

	list = NULL;
	i = 1;
	while (ag[i])
	{
		number = ft_atoi(ag[i]);
		if (!is_valid_input(ag[i], number))
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		if (is_duplicate(list, number))
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		node = new_int_node(number);
		if (!node)
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		i++;
	}
	return (list);
}

t_swap	*get_init_swap()
{
	t_swap	*input;
	input = malloc(sizeof *input);
	if (!input)
		return (NULL);
	input->stack_a = NULL;
	input->stack_b = NULL;
	input->asize = 0;
	input->bsize = 0;
	return (input);
}

int	main(int ac, char **args)
{
	t_swap	*input;

	if (ac < 2)
		return (0);
	input = get_init_swap();
	if (!input)
		return (exit_with_error());
	input->stack_a = get_input_values(args);
	if (!input->stack_a)
	{
		free(input);
		return (exit_with_error());
	}
	ft_lstclear(&input->stack_a, free);
	free(input);
	return (0);
}
