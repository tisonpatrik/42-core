/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:15:00 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:28:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Deletes and frees a single node
 *
 * This function takes a node as parameter 
 * and frees its content using
 * the function 'del'. It then frees the 
 * node itself but does NOT free
 * the next node.
 *
 * @param lst The node to free
 * @param del The address of the function 
 * used to delete the content
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del((*lst).content);
	free(lst);
}

/*
#include<stdio.h>
void	del_content(void *content)
{
	(void)content;
}

int	main(void)
{
	t_list *node1 = ft_lstnew("one");
	t_list *node2 = ft_lstnew("two");
	t_list *node3 = ft_lstnew("three");

	t_list *head = node1;
	ft_lstadd_front(&head, node2); // head = node2
	ft_lstadd_front(&head, node3); // head = node3

	ft_lstdelone(node2, del_content);
	node3->next = node1;

	while (head)
	{
		printf("Node: %s\n", (char *)head->content);
		head = head->next;
	}

	// Clean up
	free(node1);
	free(node3);
	return 0;
}
*/
