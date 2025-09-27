/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/list.h"

/**
 * @brief Adds a node at the end of the list
 *
 * This function adds the node 'new' at the end of the list.
 * If the list is empty, the new node becomes the first node.
 *
 * @param lst The address of a pointer to the first node of a list
 * @param node The address of a pointer to the node to be added
 */
void	ft_lstadd_back(t_list **lst, t_list *node)
{
	t_list	*last;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	last = ft_lstlast(*lst);
	(*last).next = node;
}

/*
t_list	*ft_lstnew(void *content);
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*content1;
	char	*content2;
	t_list	*node1;
	t_list	*node2;
	t_list	*head;

	content1 = "head";
	content2 = "new";
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	head = node1;
	ft_lstadd_back(&head, node2);
	printf("1st node content: %s\n", (char *)head->content);
	printf("2nd node content: %s\n", (char *)head->next->content);
	// Clean up
	free(node1);
	free(node2);
	return (0);
}
*/
