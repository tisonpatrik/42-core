/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:49:46 by ptison            #+#    #+#             */
/*   Updated: 2025/09/12 19:21:44 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/separator.h"
#include <stdbool.h>
#include <stdlib.h>

void	free_lis_arena(t_lis_computation *computation)
{
	if (!computation)
		return ;
	free(computation->nodes);
	free(computation->values);
	free(computation->lis_lengths);
	free(computation->previous_indices);
	free(computation);
}

t_lis_computation	*allocate_lis_arena(int element_count)
{
	t_lis_computation	*computation;

	computation = malloc(sizeof(*computation));
	if (!computation)
		return (NULL);
	computation->n = element_count;
	computation->nodes = malloc(sizeof(*computation->nodes) * (size_t)element_count);
	computation->values = malloc(sizeof(*computation->values) * (size_t)element_count);
	computation->lis_lengths = malloc(sizeof(*computation->lis_lengths) * (size_t)element_count);
	computation->previous_indices = malloc(sizeof(*computation->previous_indices) * (size_t)element_count);
	if (!computation->nodes || !computation->values || !computation->lis_lengths || !computation->previous_indices)
	{
		free_lis_arena(computation);
		return (NULL);
	}
	return (computation);
}

