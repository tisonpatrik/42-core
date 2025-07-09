/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:13:37 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 18:58:50 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

/**
 * @brief Compares memory areas
 *
 * This function compares the first n bytes of the memory areas s1 and s2.
 * It mimics the behavior of the standard memcmp function.
 * The comparison is done using unsigned characters.
 *
 * @param s1 Pointer to first memory area
 * @param s2 Pointer to second memory area
 * @param n Number of bytes to compare
 * @return <0 if s1 is less than s2, 0 if equal, >0 if s1 is greater than s2
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;
	int				diff;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		diff = ptr1[i] - ptr2[i];
		if (diff)
			return (diff);
		i++;
	}
	return (0);
}

/*
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s1 = "Hello, my friend.";
    char *s2 = "Hello, my fiend.";
    size_t n = strlen(s1);

    int expected = memcmp(s1, s2, n);
    int current = ft_memcmp(s1, s2, n);

    printf("expected: %d\n", expected);
    printf("current:  %d\n", current);

    assert((expected == 0 && current == 0) || (expected * current > 0));
    return 0;
}
*/
