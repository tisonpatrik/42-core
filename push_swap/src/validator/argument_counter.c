/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_counter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:22:09 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 18:22:18 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

static int	count_words_in_string(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != CH_SPACE)
		{
			count++;
			while (str[i] && str[i] != CH_SPACE)
				i++;
		}
		else
		{
			i++;
		}
	}
	return (count);
}

t_count_of_arguments	get_count_of_arguments(int argc, char *argv[])
{
	int	total;
	int	i;

	total = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_is_null_or_empty(argv[i]))
			return (create_count_of_arguments(0, FAILURE));
		total += count_words_in_string(argv[i]);
		i++;
	}
	return (create_count_of_arguments(total, SUCCESS));
}
