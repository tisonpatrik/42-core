/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:17:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 18:58:56 by ptison           ###   ########.fr       */
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

static void	store_token(const char *tok, int *out, int *out_index)
{
	char	*endptr;
	int		val;

	endptr = NULL;
	if (!tok || tok[0] == '\0')
	{
		store_value(INT_MIN, out, out_index);
		return ;
	}
	errno = 0;
	val = ft_strtoi10(tok, &endptr);
	if (*endptr != '\0' || errno == ERANGE)
	{
		store_value(INT_MIN, out, out_index);
		return ;
	}
	store_value(val, out, out_index);
}

static void	fill_from_parts(char *str, int *out, int *out_index)
{
	int		j;
	char	**parts;

	j = 0;
	parts = ft_split(str, CH_SPACE);
	if (!parts)
		return ;
	while (parts[j])
	{
		store_token(parts[j], out, out_index);
		j++;
	}
	ft_free_array(parts);
}

void	fill_numbers(int argc, char *argv[], int *out)
{
	int		out_index;
	int		i;

	out_index = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], CH_SPACE))
		{
			fill_from_parts(argv[i], out, &out_index);
		}
		else
		{
			store_token(argv[i], out, &out_index);
		}
		i++;
	}
}
