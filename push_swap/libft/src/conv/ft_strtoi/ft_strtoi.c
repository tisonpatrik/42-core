#include <errno.h>
#include <limits.h>
#include "../../../include/ft/core.h"
#include "../../../include/ft/conv.h"
#include "../../../include/ft/utils.h"
#include "../../../include/ft/ft_strtoi.h"

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
 * @brief Check if digit would cause overflow
 *
 * @param current_accumulated Current accumulated value
 * @param overflow_threshold Overflow threshold
 * @param last_digit_limit Last digit threshold
 * @param current_digit Current digit
 * @return 1 if overflow would occur, 0 otherwise
 */
int	would_overflow(unsigned int current_accumulated, unsigned int overflow_threshold,
		unsigned int last_digit_limit, unsigned int current_digit)
{
	if (current_accumulated > overflow_threshold)
		return (1);
	else if (current_accumulated == overflow_threshold && current_digit > last_digit_limit)
		return (1);
	return (0);
}

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
	unsigned int		current_digit;

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
				result.accumulated_value = result.accumulated_value * 10 + current_digit;
			result.digits_found = 1;
		}
		else
			break;
		(*current_position)++;
	}
	return (result);
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

int	ft_strtoi10(const char *nptr, char **endptr)
{
	const char		*current_position;
	int			is_negative;
	unsigned int		overflow_threshold;
	unsigned int		last_digit_limit;
	struct s_parse_result	result;

	current_position = nptr;
	is_negative = 0;
	ft_skip_whitespace(&current_position);
	is_negative = ft_parse_sign(&current_position);
	overflow_threshold = calculate_cutoff(is_negative);
	last_digit_limit = calculate_cutlim(&overflow_threshold);
	result = parse_digits(&current_position, overflow_threshold, last_digit_limit);
	set_endptr(endptr, nptr, current_position, result.digits_found);
	if (result.overflow_detected)
		return (handle_overflow(is_negative));
	if (is_negative)
		return (-(int)result.accumulated_value);
	else
		return ((int)result.accumulated_value);
}
