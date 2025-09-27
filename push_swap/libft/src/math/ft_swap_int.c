/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:05:00 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Swaps two integer values
 *
 * This function swaps the values of two integers pointed to by the given
 * pointers.
 *
 * @param a Pointer to first integer
 * @param b Pointer to second integer
 */
void	ft_swap_int(int *a, int *b)
{
	int	temp;

	if (!a || !b)
		return ;
	temp = *a;
	*a = *b;
	*b = temp;
}
