/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:31 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/str.h"
#include <stdlib.h>

/**
 * @brief Concatenates two strings
 *
 * This function allocates and returns a new string, which is the result
 * of the concatenation of 's1' and 's2'. Memory for the new string is
 * obtained with malloc and can be freed with free.
 *
 * @param s1 The prefix string
 * @param s2 The suffix string
 * @return The new concatenated string, or NULL if the allocation fails
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	total;
	char	*result;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total = len_s1 + len_s2 + 1;
	result = malloc(total * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total);
	ft_strlcat(result, s2, total);
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*result;

	s1 = "hello, ";
	s2 = "my friend!";
	result = ft_strjoin(s1, s2);
	printf("%s \n", result);
	free(result);
	return (0);
}
*/
