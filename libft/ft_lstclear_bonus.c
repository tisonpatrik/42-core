/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:23:19 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:29:28 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Deletes and frees the entire list
 *
 * This function deletes and frees the given node and all its successors,
 * using the function 'del' and free. Finally, it sets the pointer to
 * the list to NULL.
 *
 * @param lst The address of a pointer to a node
 * @param del The address of the function used to delete the content of the node
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = (*current).next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}

/*
#include <stdio.h>

void	del_content(void *content)
{
	(void)content;
}

int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*head;

	node1 = ft_lstnew("one");
	node2 = ft_lstnew("two");
	node3 = ft_lstnew("three");
	head = node1;
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);
	printf("Before clear:\n");
	while (head)
	{
		printf("Node: %s\n", (char *)head->content);
		head = head->next;
	}
	ft_lstclear(&head, del_content);
	printf("\nAfter clear:\n");
	if (!head)
		printf("List is empty.\n");
	return (0);
}
*/
