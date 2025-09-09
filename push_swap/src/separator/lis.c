/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:25:49 by patrik            #+#    #+#             */
/*   Updated: 2025/09/09 19:25:49 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/separator.h"
#include "../../include/stack.h"
#include <stdbool.h>
#include <stdlib.h>

t_node_bool_array	*get_lis_nodes(t_stack *stack)
{
	int					n;
	t_node_bool_array	*result;

	n = get_size(stack);
	if (n <= 0)
	{
		result = malloc(sizeof(*result));
		if (!result)
			return (NULL);
		result->items = NULL;
		result->count = 0;
		return (result);
	}
	return (get_lis_nodes_impl(stack, n));
}
