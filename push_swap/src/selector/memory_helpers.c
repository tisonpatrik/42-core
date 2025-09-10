/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:56:08 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:59:22 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../include/selector.h"

#define CLEANUP_INITIAL_CAPACITY 8

typedef struct s_cleanup_list
{
	void	**ptrs;
	int		count;
	int		capacity;
}	t_cleanup_list;

t_cleanup_list	*new_cleanup_list(void)
{
	t_cleanup_list	*list;

	list = malloc(sizeof(t_cleanup_list));
	if (!list)
		return (NULL);
	list->ptrs = malloc(sizeof(void *) * CLEANUP_INITIAL_CAPACITY);
	if (!list->ptrs)
	{
		free(list);
		return (NULL);
	}
	list->count = 0;
	list->capacity = CLEANUP_INITIAL_CAPACITY;
	return (list);
}

void	add_to_cleanup(t_cleanup_list *list, void *ptr)
{
	void	**new_ptrs;

	if (!list || !ptr)
		return;
	if (list->count >= list->capacity)
	{
		new_ptrs = malloc(sizeof(void *) * list->capacity * 2);
		if (!new_ptrs)
			return;
		ft_memcpy(new_ptrs, list->ptrs, sizeof(void *) * list->count);
		free(list->ptrs);
		list->ptrs = new_ptrs;
		list->capacity *= 2;
	}
	list->ptrs[list->count] = ptr;
	list->count++;
}

void	cleanup_all(t_cleanup_list *list)
{
	int	i;

	if (!list)
		return;
	i = 0;
	while (i < list->count)
	{
		if (list->ptrs[i])
			free(list->ptrs[i]);
		i++;
	}
	free(list->ptrs);
	free(list);
}

void	*safe_malloc_with_cleanup(size_t size, t_cleanup_list *cleanup)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (cleanup)
		add_to_cleanup(cleanup, ptr);
	return (ptr);
}