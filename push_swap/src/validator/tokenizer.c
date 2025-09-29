/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:17:51 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 09:54:48 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"




static int	get_count_of_parts(char **parts)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	if (!parts)
		fatal_cleanup_and_exit(NULL, NULL);
	while (parts[j])
	{
		if (parts[j][0] == '\0')
			fatal_cleanup_and_exit(NULL, parts);
		count++;
		j++;
	}
	return (count);
}


t_count_of_arguments	get_count_of_arguments(int argc, char *argv[])
{
	int		total;
	int		i;
	char	**parts;

	total = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_is_null_or_empty(argv[i]))
			return (create_count_of_arguments(0, FAILURE));
		
		if (ft_strchr(argv[i], CH_SPACE))
		{
			parts = ft_split(argv[i], CH_SPACE);
			total += get_count_of_parts(parts);
			ft_free_array(parts);
		}
		else
		{
			total++;
		}
		i++;
	}
	return (total);
}
