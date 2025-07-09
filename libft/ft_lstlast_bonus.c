/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:25 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:32:52 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the last node of the list
 *
 * This function traverses the list and returns a pointer to the last node.
 * If the list is empty, it returns NULL.
 *
 * @param lst The beginning of the list
 * @return Last node of the list, or NULL if the list is empty
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while ((*lst).next)
		lst = (*lst).next;
	return (lst);
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
	t_list		*last;

	content1 = "head";
	content2 = "new";
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	head = node1;
	ft_lstadd_front(&head, node2);
	last = ft_lstlast(head);
	printf("last: %s \n", (char*)last->content);
	// Clean up
	free(node1);
	free(node2);
	return (0);
}
*/
