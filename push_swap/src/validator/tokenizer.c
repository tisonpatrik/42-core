/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:17:51 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 16:52:55 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

static void	store_value(int value, int *out, int *out_index)
{
	int	current_index;

	current_index = *out_index;
	out[current_index] = value;
	*out_index = current_index + 1;
}

static bool	store_token(const char *tok, int *out, int *out_index)
{
	char	*endptr;
	int		val;

	endptr = NULL;
	if (!tok || tok[0] == '\0')
	{
		store_value(INT_MIN, out, out_index);
		return (false);
	}
	errno = 0;
	val = ft_strtoi10(tok, &endptr);
	if (*endptr != '\0' || errno == ERANGE)
	{
		store_value(INT_MIN, out, out_index);
		return (false);
	}
	store_value(val, out, out_index);
	return (true);
}

static bool	fill_from_parts(char *str, int *out, int *out_index)
{
	int		j;
	char	**parts;
	bool	all_valid;

	j = 0;
	all_valid = true;
	parts = ft_split(str, CH_SPACE);
	if (!parts)
		return (false);
	while (parts[j])
	{
		if (!store_token(parts[j], out, out_index))
			all_valid = false;
		j++;
	}
	ft_free_array(parts);
	return (all_valid);
}

bool	fill_numbers(int argc, char *argv[], int *out)
{
	int		out_index;
	int		i;
	bool	all_valid;

	out_index = 0;
	i = 1;
	all_valid = true;
	while (i < argc)
	{
		if (ft_strchr(argv[i], CH_SPACE))
		{
			if (!fill_from_parts(argv[i], out, &out_index))
				all_valid = false;
		}
		else
		{
			if (!store_token(argv[i], out, &out_index))
				all_valid = false;
		}
		i++;
	}
	return (all_valid);
}
