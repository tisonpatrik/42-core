/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:54:00 by ptison            #+#    #+#             */
/*   Updated: 2025/08/19 18:54:04 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Parses sign character and advances pointer
 *
 * This function parses the sign character at the current position
 * and advances the pointer accordingly. It handles positive and negative
 * signs, returning appropriate values and modifying the pointer position.
 *
 * @param p Pointer to pointer of current position in string
 * @return 1 if negative sign found, 0 if positive or no sign
 */
int	ft_parse_sign(const char **p)
{
	if (**p == '+')
	{
		(*p)++;
		return (0);
	}
	else if (**p == '-')
	{
		(*p)++;
		return (1);
	}
	return (0);
}
