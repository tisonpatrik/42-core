/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:21:58 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:34:18 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of nodes in a list
 *
 * This function counts the number of nodes in the list starting
 * from the given node.
 *
 * @param lst The beginning of the list
 * @return The length of the list
 */
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = (*lst).next;
	}
	return (count);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*content1;
	char	*content2;
	t_list	*node1;
	t_list	*node2;
	t_list	*head;
	int		count;

	content1 = "lst";
	content2 = "new";
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	head = node1;
	ft_lstadd_front(&head, node2);
	count = ft_lstsize(head);
	printf("count: %d \n", count);
	// Clean up
	free(node1);
	free(node2);
	return (0);
}
*/
