/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:23:06 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:33:00 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds a node at the beginning of the list
 *
 * This function adds the node 'new' at the beginning of the list.
 * The new node becomes the first node of the list.
 *
 * @param lst The address of a pointer to the first node of a list
 * @param new The address of a pointer to the node to be added
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	(*new).next = *lst;
	*lst = new;
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

	content1 = "lst";
	content2 = "new";
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	head = node1;
	ft_lstadd_front(&head, node2);
	printf("1st node content: %s\n", (char *)head->content);
	printf("2nd node content: %s\n", (char *)head->next->content);
	// Clean up
	free(node1);
	free(node2);
	return (0);
}
*/
