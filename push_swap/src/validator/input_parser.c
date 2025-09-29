/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:04 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 19:04:37 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

static bool	has_duplicates(int *arr, int n)
{
	int	i;

	if (n < 2)
		return (false);
	ft_heap_sort(arr, n);
	i = 1;
	while (i < n)
	{
		if (arr[i] == arr[i - 1])
			return (true);
		i++;
	}
	return (false);
}

static bool	has_negative_numbers(int *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (arr[i] < 0)
			return (false);
		i++;
	}
	return (true);
}

t_parser_result	parse_args(int argc, char *argv[])
{
	t_count_of_arguments	count;
	int						*buf;

	if (argc < 2)
		return (create_parser_result(NULL, 0, NO_ARGS));
	count = get_count_of_arguments(argc, argv);
	buf = (int *)malloc(sizeof(int) * count.count);
	if (!buf)
		return (create_parser_result(NULL, 0, FAILURE));
	fill_numbers(argc, argv, buf);
	if (has_duplicates(buf, count.count)||!has_negative_numbers(buf, count.count))
		return (create_parser_result(buf, count.count, FAILURE));
	return (create_parser_result(buf, count.count, SUCCESS));
}
