/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:56:40 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 12:18:24 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtoi_internal.h"


/**
 * @brief Calculate cutoff value for overflow detection
 *
 * @param is_negative Whether the number is negative
 * @return The cutoff value
 */
unsigned int	calculate_cutoff(int is_negative)
{
	if (is_negative)
		return ((unsigned int)(-(long)INT_MIN));
	else
		return ((unsigned int)INT_MAX);
}

/**
 * @brief Calculate cutlim value and update cutoff
 *
 * @param cutoff_value Pointer to cutoff value (will be modified)
 * @return The cutlim value
 */
unsigned int	calculate_cutlim(unsigned int *cutoff_value)
{
	unsigned int	last_digit_limit;

	last_digit_limit = *cutoff_value % 10;
	*cutoff_value = *cutoff_value / 10;
	return (last_digit_limit);
}

/**
 * @brief Set endptr to appropriate position
 *
 * @param end_pointer Pointer to end pointer
 * @param original_string_start Original string start
 * @param current_position Current position
 * @param digits_found Whether any digits were found
 */
void	set_endptr(char **end_pointer, const char *original_string_start,
		const char *current_position, int digits_found)
{
	if (end_pointer)
	{
		if (!digits_found)
			*end_pointer = (char *)original_string_start;
		else
			*end_pointer = (char *)current_position;
	}
}

/**
 * @brief Check if digit would cause overflow
 *
 * @param current_accumulated Current accumulated value
 * @param overflow_threshold Overflow threshold
 * @param last_digit_limit Last digit threshold
 * @param current_digit Current digit
 * @return 1 if overflow would occur, 0 otherwise
 */
int	would_overflow(unsigned int current_accumulated,
		unsigned int overflow_threshold, unsigned int last_digit_limit,
		unsigned int current_digit)
{
	if (current_accumulated > overflow_threshold)
		return (1);
	else if (current_accumulated == overflow_threshold
		&& current_digit > last_digit_limit)
		return (1);
	return (0);
}

/**
 * @brief Handle overflow case
 *
 * @param is_negative Whether number is negative
 * @return INT_MIN or INT_MAX
 */
int	handle_overflow(int is_negative)
{
	errno = ERANGE;
	if (is_negative)
		return (INT_MIN);
	else
		return (INT_MAX);
}
