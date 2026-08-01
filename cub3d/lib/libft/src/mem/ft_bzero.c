/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Sets the first n bytes of memory to zero
 *
 * This function sets the first n bytes of the memory area pointed to by str
 * to zero (bytes containing '\0'). It mimics the behavior of the standard
 * bzero function. This function is commonly used to initialize memory areas.
 *
 * @param str Pointer to the memory area to be zeroed
 * @param n Number of bytes to set to zero
 * @return Pointer to the memory area str
 */
void	*ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
	return (str);
}
