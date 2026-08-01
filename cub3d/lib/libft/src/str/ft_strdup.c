/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:12:25 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

/**
 * @brief Duplicates a string
 *
 * This function creates a new string which is a duplicate of the string s.
 * Memory for the new string is obtained with malloc, and can be freed with free.
 * It mimics the behavior of the standard strdup function.
 *
 * @param s The string to duplicate
 * @return A pointer to the duplicated string, or NULL if insufficient memory
 */
char	*ft_strdup(const char *s)
{
	size_t	len;
	int		i;
	char	*new_string;

	len = ft_strlen(s);
	new_string = malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
