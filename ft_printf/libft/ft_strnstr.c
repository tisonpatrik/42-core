/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:18:42 by ptison            #+#    #+#             */
/*   Updated: 2025/05/26 19:09:12 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	within_len(size_t i, size_t j, size_t len)
{
	return ((i + j) < len);
}

int	not_null_terminated(const char *s, size_t index)
{
	return (s[index] != '\0');
}

int	chars_match(const char *big, const char *little, size_t i, size_t j)
{
	return (big[i + j] == little[j]);
}

int	is_little_ended(const char *little, size_t j)
{
	return (little[j + 1] == '\0');
}

/**
 * @brief Locates a substring in a string with length limit
 *
 * This function locates the first occurrence of the null-terminated string
 * little in the string big, where not more than len characters are searched.
 * Characters that appear after a '\0' character are not searched.
 * It mimics the behavior of the BSD strnstr function.
 *
 * @param big The string to search in
 * @param little The substring to search for
 * @param len The maximum number of characters to search
 * @return Pointer to the first occurrence of little, or NULL if not found
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && not_null_terminated(big, i))
	{
		j = 0;
		while (within_len(i, j, len) && not_null_terminated(big, i + j)
			&& chars_match(big, little, i, j))
		{
			if (is_little_ended(little, j))
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
#include <assert.h>
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	const char	big[30] = "aaabcabcd";
	const char	little[] = "cd";
	size_t		len;
	char		*expected;
	char		*current;

	len = 8;
	expected = strnstr(big, little, len);
	printf("expected: %s\n", expected);
	current = ft_strnstr(big, little, len);
	printf("current:  %s\n", current);
	assert((expected == NULL && current == NULL) || (strcmp(expected,
				current) == 0));
	return (0);
}
*/
