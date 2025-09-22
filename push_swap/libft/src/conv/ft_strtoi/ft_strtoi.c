/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:54:44 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:29:15 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/conv.h"
#include "../../../include/core.h"
#include "../../../include/ft_strtoi.h"
#include "../../../include/utils.h"
#include <limits.h>

unsigned int			calculate_cutoff(int is_negative);
unsigned int			calculate_cutlim(unsigned int *cutoff_value);
int						would_overflow(unsigned int current_accumulated,
							unsigned int overflow_threshold,
							unsigned int last_digit_limit,
							unsigned int current_digit);

int						handle_overflow(int is_negative);

void					set_endptr(char **end_pointer,
							const char *original_string_start,
							const char *current_position, int digits_found);

/**
 * @brief Parse digits and build number
 *
 * @param current_position Pointer to current position
 * @param overflow_threshold Overflow threshold
 * @param last_digit_limit Last digit threshold
 * @return Tuple of (accumulated_value, overflow_flag, any_digits_flag)
 */
struct s_parse_result	parse_digits(const char **current_position,
		unsigned int overflow_threshold, unsigned int last_digit_limit)
{
	struct s_parse_result	result;
	unsigned int			current_digit;

	result.accumulated_value = 0;
	result.overflow_detected = 0;
	result.digits_found = 0;
	while (**current_position)
	{
		if (ft_isdigit(**current_position))
		{
			current_digit = (unsigned int)(**current_position - '0');
			if (would_overflow(result.accumulated_value, overflow_threshold,
					last_digit_limit, current_digit))
				result.overflow_detected = 1;
			else
				result.accumulated_value = result.accumulated_value * 10
					+ current_digit;
			result.digits_found = 1;
		}
		else
			break ;
		(*current_position)++;
	}
	return (result);
}

int	ft_strtoi10(const char *nptr, char **endptr)
{
	const char				*current_position;
	int						is_negative;
	unsigned int			overflow_threshold;
	unsigned int			last_digit_limit;
	struct s_parse_result	result;

	current_position = nptr;
	is_negative = 0;
	ft_skip_whitespace(&current_position);
	is_negative = ft_parse_sign(&current_position);
	overflow_threshold = calculate_cutoff(is_negative);
	last_digit_limit = calculate_cutlim(&overflow_threshold);
	result = parse_digits(&current_position, overflow_threshold,
			last_digit_limit);
	set_endptr(endptr, nptr, current_position, result.digits_found);
	if (result.overflow_detected)
		return (handle_overflow(is_negative));
	if (is_negative)
		return (-(int)result.accumulated_value);
	else
		return ((int)result.accumulated_value);
}
