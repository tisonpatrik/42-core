/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str8_to_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:38:04 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:38:05 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv.h"
#include "core.h"

static bool	parse_digit(unsigned int *value, unsigned int limit, uint8_t digit)
{
	unsigned int	number;

	number = digit - '0';
	if (*value > limit / 10
		|| (*value == limit / 10 && number > limit % 10))
		return (false);
	*value = *value * 10 + number;
	return (true);
}

static bool	parse_sign(t_str8 text, size_t *index, int *sign)
{
	*index = 0;
	*sign = 1;
	if (*index < text.len
		&& (text.str[*index] == '+' || text.str[*index] == '-'))
	{
		if (text.str[*index] == '-')
			*sign = -1;
		(*index)++;
	}
	return (*index < text.len);
}

static bool	parse_value(t_str8 text, size_t index, unsigned int limit,
	unsigned int *value)
{
	*value = 0;
	while (index < text.len && ft_isdigit(text.str[index]))
	{
		if (!parse_digit(value, limit, text.str[index]))
			return (false);
		index++;
	}
	return (index == text.len);
}

bool	ft_str8_to_int(t_str8 text, int *result)
{
	unsigned int	value;
	unsigned int	limit;
	size_t			i;
	int				sign;

	if (!result || !text.str)
		return (false);
	text = ft_str8_trim(text);
	if (!parse_sign(text, &i, &sign))
		return (false);
	limit = INT_MAX;
	if (sign < 0)
		limit++;
	if (!parse_value(text, i, limit, &value))
		return (false);
	if (sign < 0 && value == (unsigned int)INT_MAX + 1)
		*result = INT_MIN;
	else
		*result = (int)value * sign;
	return (true);
}
