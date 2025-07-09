/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:57 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:33:08 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds a node at the end of the list
 *
 * This function adds the node 'new' at the end of the list.
 * If the list is empty, the new node becomes the first node.
 *
 * @param lst The address of a pointer to the first node of a list
 * @param new The address of a pointer to the node to be added
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	(*last).next = new;
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
