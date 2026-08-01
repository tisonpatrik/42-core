/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

/**
 * @brief Adds a node at the beginning of the list
 *
 * This function adds the node 'new' at the beginning of the list.
 * The new node becomes the first node of the list.
 *
 * @param lst The address of a pointer to the first node of a list
 * @param node The address of a pointer to the node to be added
 */
void	ft_lstadd_front(t_list **lst, t_list *node)
{
	if (!lst || !node)
		return ;
	(*node).next = *lst;
	*lst = node;
}
