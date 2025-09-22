/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:04 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:30:08 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>

int	get_count_of_arguments(int argc, char *argv[])
{
	int		total;
	int		i;
	char	**parts;

	total = 0;
	i = 1;
	while (i < argc)
	{
		if (!argv[i] || argv[i][0] == '\0')
			fatal_cleanup_and_exit(NULL, NULL);
		if (ft_strchr(argv[i], ' '))
		{
			parts = ft_split(argv[i], ' ');
			total += count_parts(parts);
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

void	fill_from_parts(char **parts, int *out, int *out_index)
{
	int	j;

	j = 0;
	if (!parts)
		fatal_cleanup_and_exit(out, NULL);
	while (parts[j])
	{
		store_token(parts[j], out, out_index, parts);
		j++;
	}
	ft_free_array(parts);
}

void	fill_numbers(int argc, char *argv[], int *out)
{
	int		out_index;
	int		i;
	char	**parts;

	out_index = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], ' '))
		{
			parts = ft_split(argv[i], ' ');
			fill_from_parts(parts, out, &out_index);
		}
		else
		{
			store_token(argv[i], out, &out_index, NULL);
		}
		i++;
	}
}

void	check_duplicates(int *arr, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (arr[i] == arr[j])
				fatal_cleanup_and_exit(arr, NULL);
			j++;
		}
		i++;
	}
}

t_parser_result	parse_args(int argc, char *argv[])
{
	t_parser_result	res;
	int				total;
	int				*buf;

	if (argc < 2)
		exit(0);
	total = get_count_of_arguments(argc, argv);
	buf = (int *)malloc(sizeof(int) * total);
	if (!buf)
		fatal_cleanup_and_exit(NULL, NULL);
	fill_numbers(argc, argv, buf);
	check_duplicates(buf, total);
	res.input = buf;
	res.count = total;
	return (res);
}
