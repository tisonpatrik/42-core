/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:16:34 by ptison            #+#    #+#             */
/*   Updated: 2025/08/15 16:13:40 by patrik           ###   ########.fr       */
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

	len = ft_strlen(original);
	if ((number == 0) && (ft_strncmp(original, "0", len) != 0))
	{
		return (0);
	}
	reverse_int = ft_itoa(number);
	reverse_len = ft_strlen(reverse_int);
	if ((reverse_len != len) || (ft_strncmp(reverse_int, original, len) != 0))
	{
		return (0);
	}
	return (1);
}
t_list	*get_input_values(char **ag)
{
	t_list	*result;
	t_list	*node;
	int		i;
	int		number;
	int		is_valid;
	int		*value;

	result = NULL;
	i = 1;
	while (ag[i])
	{
		number = ft_atoi(ag[i]);
		is_valid = is_valid_input(ag[i], number);
		if (is_valid == 0)
		{
			ft_lstclear(&result, free);
			return (NULL);
		}
		value = malloc(sizeof *value);
		if (!value)
		{
			ft_lstclear(&result, free);
			return (NULL);
		}
		*value = number;
		node = ft_lstnew(value);
		if (!node)
		{
			free(value);
			ft_lstclear(&result, free);
			return (NULL);
		}
		ft_lstadd_back(&result, node);
		i++;
	}
	return (result);
}

t_swap	*get_init_swap(int ac)
{
	t_swap	*input;

	if (ac < 2)
		return (NULL);
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

	input = get_init_swap(ac);
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
