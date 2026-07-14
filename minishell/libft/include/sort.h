/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:29:01 by ptison            #+#    #+#             */
/*   Updated: 2026/02/26 12:05:37 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <stddef.h>
# include <sys/types.h>

void	ft_heap_sort_ptr(void **arr, size_t n, int (*cmp)(void *, void *));

#endif
