/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:12 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:32:47 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Creates a new list by applying a function to each node
 *
 * This function iterates through the list 'lst', applies the function 'f'
 * to each node's content, and creates a new list resulting from the
 * successive applications of the function 'f'. The 'del' function is used
 * to delete the content of a node if needed.
 *
 * @param lst The address of a pointer to a node
 * @param f The address of the function applied to each node's content


	* @param del The address of the function used to delete
	* a node's content if needed
 * @return The new list, or NULL if the allocation fails
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_content = f((*lst).content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = (*lst).next;
	}
	return (new_list);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

void *to_uppercase_dup(void *content)
{
	char *str = (char *)content;
	char *copy = strdup(str);
	if (!copy)
		return NULL;
	for (int i = 0; copy[i]; i++)
		copy[i] = (char)toupper((unsigned char)copy[i]);
	return copy;
}

void del_content(void *content)
{
	free(content);
}

void print_list(t_list *lst)
{
	while (lst)
	{
		printf("Node: %s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	main(void)
{
	char *s1 = strdup("hello");
	char *s2 = strdup("world");
	char *s3 = strdup("list");

	t_list *n1 = ft_lstnew(s1);
	t_list *n2 = ft_lstnew(s2);
	t_list *n3 = ft_lstnew(s3);

	t_list *original = n1;
	ft_lstadd_front(&original, n2);
	ft_lstadd_front(&original, n3);

	printf("Original list:\n");
	print_list(original);

	t_list *mapped = ft_lstmap(original, to_uppercase_dup, del_content);

	printf("\nMapped list:\n");
	print_list(mapped);

	free(s1);
	free(s2);
	free(s3);
	free(n1);
	free(n2);
	free(n3);
	ft_lstclear(&mapped, del_content);

	return 0;
}
*/
