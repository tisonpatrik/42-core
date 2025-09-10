/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:14:34 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:14:36 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/selector.h"

bool	is_empty(int *arr, int size)
{
	(void)arr;
	return (size == 0);
}

bool	is_empty_or_single(int *arr, int size)
{
	(void)arr;
	return (size <= 1);
}
