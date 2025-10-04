/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:04 by ptison            #+#    #+#             */
/*   Updated: 2025/10/04 18:11:40 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

static bool	has_duplicates(int *arr, int n)
{
	int	*copy;
	int	i;

	if (n < 2)
		return (false);
	copy = malloc(sizeof(int) * n);
	if (!copy)
		return (true);
	ft_memcpy(copy, arr, sizeof(int) * n);
	ft_heap_sort(copy, n);
	i = 1;
	while (i < n)
	{
		if (copy[i] == copy[i - 1])
		{
			free(copy);
			return (true);
		}
		i++;
	}
	free(copy);
	return (false);
}

static bool	has_int_min(int *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (arr[i] == INT_MIN)
			return (true);
		i++;
	}
	return (false);
}

t_parser_result	parse_args(int argc, char *argv[])
{
	t_count_of_arguments	count;
	int						*buf;
	int						*normalized;

	if (argc < 2)
		return (create_parser_result(NULL, 0, NO_ARGS));
	count = get_count_of_arguments(argc, argv);
	buf = (int *)malloc(sizeof(int) * count.count);
	if (!buf)
		return (create_parser_result(NULL, 0, FAILURE));
	fill_numbers(argc, argv, buf);
	if (has_duplicates(buf, count.count) || has_int_min(buf, count.count))
	{
		free(buf);
		return (create_parser_result(NULL, count.count, FAILURE));
	}
	normalized = indexize_array(buf, count.count);
	free(buf); 
	if (!normalized)
		return (create_parser_result(NULL, count.count, FAILURE));
	
	return (create_parser_result(normalized, count.count, SUCCESS));
}
