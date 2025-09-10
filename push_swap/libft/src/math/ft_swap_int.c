/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:22 by patrik            #+#    #+#             */
/*   Updated: 2025/09/10 22:07:04 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * @brief Swaps two integer values
 *
 * This function swaps the values of two integers pointed to by the parameters.
 * It uses a temporary variable to perform the swap operation.
 *
 * @param a Pointer to the first integer
 * @param b Pointer to the second integer
 */
void	ft_swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
