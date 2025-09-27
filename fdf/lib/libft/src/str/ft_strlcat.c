/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/str.h"

/**
 * @brief Concatenate string to a specific size
 *
 * This function appends the src string to the dest string,
 * overwriting the terminating null byte at the end of dest,
 * and then adds a terminating null byte. The strings may not overlap.
 * It mimics the behavior of the BSD strlcat function.
 *
 * @param dest The destination buffer
 * @param src The source string
 * @param dsize The size of the destination buffer
 * @return The total length of the string tried to create
 */
size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (dsize <= dest_len)
		return (src_len + dsize);
	while (src[i] && (dest_len + i < dsize - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}

/*
#include <assert.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	const char	*src = "Hello.";
	size_t		size;
	char		dest[20] = "Baf!!";
	int			count;
	char		my_dest[20] = "Baf!!";
	int			my_count;

	size = 10;
	printf("BEFORE (libc): dest = \"%s\"\n", dest);
	count = strlcat(dest, src, size);
	printf("AFTER  (libc): dest = \"%s\", return (= %d\n\n", dest, count));
	printf("BEFORE (ft_):  my_dest = \"%s\"\n", my_dest);
	my_count = ft_strlcat(my_dest, src, size);
	printf("AFTER  (ft_):  my_dest = \"%s\", return (= %d\n", my_dest,
		my_count));
	assert(strcmp(dest, my_dest) == 0);
	assert(count == my_count);
	return (0);
}
*/
