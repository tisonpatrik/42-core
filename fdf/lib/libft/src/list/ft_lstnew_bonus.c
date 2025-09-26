/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:15:00 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/list.h"
#include <stdlib.h>

/**
 * @brief Creates a new list node
 *
 * This function allocates memory for
 * a new node and initializes it.
 * The 'content' member variable is
 * initialized with the given parameter.
 * The 'next' variable is initialized to NULL.
 *
 * @param content The content to store in the new node
 * @return A pointer to the new node, or NULL if allocation fails
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	(*new_node).content = content;
	(*new_node).next = NULL;
	return (new_node);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*content;
	t_list	*node;

	content = "hello";
	node = ft_lstnew(content);
	if (!node)
		return (1);
	printf("content: %s\n", (char *)node->content);
	printf("next: %p\n", (void *)node->next);
	free(node);
	return (0);
}
*/
