/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:10:06 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 15:11:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"

size_t	calculate_lis_length(t_node **lis_nodes)
{
	size_t	count;

	count = 0;
	while (lis_nodes[count] != NULL)
		count++;
	return (count);
}

bool	is_node_in_lis(t_node *node, t_node **lis_nodes, size_t lis_count)
{
	size_t	i;

	if (!node || !lis_nodes)
		return (false);
	i = 0;
	while (i < lis_count)
	{
		if (lis_nodes[i] == node)
			return (true);
		i++;
	}
	return (false);
}
