/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:22:37 by patrik            #+#    #+#             */
/*   Updated: 2025/05/26 19:32:54 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates through the list and applies a function to each node
 *
 * This function iterates through the list 'lst' and applies the function 'f'
 * to the content of each node.
 *
 * @param lst The address of a pointer to a node
 * @param f The address of the function to apply to each node's content
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f((*lst).content);
		lst = (*lst).next;
	}
}

/*
#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	to_uppercase(void *content)
{
	char	*str;

	str = (char *)content;
	while (*str)
	{
		*str = (char)toupper((unsigned char)*str);
		str++;
	}
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("Node: %s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;
	t_list	*head;

	s1 = strdup("hello");
	s2 = strdup("world");
	s3 = strdup("list");
	n1 = ft_lstnew(s1);
	n2 = ft_lstnew(s2);
	n3 = ft_lstnew(s3);
	head = n1;
	ft_lstadd_front(&head, n2);
	ft_lstadd_front(&head, n3); // head → n3 → n2 → n1
	printf("Before ft_lstiter:\n");
	print_list(head);
	ft_lstiter(head, to_uppercase);
	printf("\nAfter ft_lstiter:\n");
	print_list(head);
	// Clean up
	free(s1);
	free(s2);
	free(s3);
	free(n1);
	free(n2);
	free(n3);
	return (0);
}
*/
