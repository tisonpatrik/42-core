/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:13:20 by ptison            #+#    #+#             */
/*   Updated: 2025/08/16 19:58:55 by ptison           ###   ########.fr       */
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

t_list	*get_input_values(char **ag)
{
	t_list	*list;
	int		i;
	t_list	*node;

	list = NULL;
	i = 1;
	while (ag[i])
	{
		node = get_node(list, node, ag[i]);
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

void    print_list(const t_list *lst)
{
    while (lst)
    {
        printf("%d\n", *(int *)lst->content);
        lst = lst->next;
    }
}
int	main(int ac, char **args)
{
	t_list	*input;

	if (ac < 2)
		return (0);
	input = get_input_values(args);
	if (!input)
	{
		free(input);
		return (exit_with_error());
	}
	print_list(input);
	ft_lstclear(&input, free);
	free(input);
	return (0);
}
