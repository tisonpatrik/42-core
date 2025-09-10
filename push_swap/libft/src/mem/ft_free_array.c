/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:05 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:07:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>

/**
 * @brief Frees a dynamically allocated array of strings
 *
 * This function safely frees a dynamically allocated array of strings (char**).
 * It first frees each individual string in the array, then frees the array itself.
 * The function handles NULL pointers gracefully.
 *
 * @param array Pointer to the array of strings to free
 */
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
