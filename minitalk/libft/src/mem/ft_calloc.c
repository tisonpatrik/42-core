/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:24:11 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mem.h"
#include <stdlib.h>

/**
 * @brief Allocates and initializes memory to zero
 *
 * This function allocates memory for an array of nelem elements of elsize bytes

	* each and returns a pointer to the allocated memory. 
	* The memory is set to zero.

	* It mimics the behavior of the standard calloc function. 
	* If overflow would occur
 * in the multiplication, the function returns NULL.
 *
 * @param nelem Number of elements to allocate
 * @param elsize Size of each element in bytes
 * @return Pointer to the allocated memory, or NULL if allocation fails
 */
void	*ft_calloc(size_t nelem, size_t elsize)
{
	size_t			total;
	void			*ptr;
	unsigned char	*byte_ptr;
	size_t			i;

	total = nelem * elsize;
	if (nelem == 0 || elsize == 0)
	{
		return (malloc(1));
	}
	if (total / nelem != elsize)
	{
		return (NULL);
	}
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	byte_ptr = ptr;
	i = 0;
	while (i < total)
	{
		byte_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
