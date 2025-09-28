/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:00:04 by ptison            #+#    #+#             */
/*   Updated: 2025/09/28 15:19:53 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"
#include <stdlib.h>

static void	store_token(const char *tok, int *out, int *out_index,
		char **parts_for_cleanup)
{
	char	*endptr;
	int		val;

	endptr = NULL;
	if (!tok || tok[0] == '\0')
		fatal_cleanup_and_exit(out, parts_for_cleanup);
	errno = 0;
	val = ft_strtoi10(tok, &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		fatal_cleanup_and_exit(out, parts_for_cleanup);
	out[(*out_index)++] = val;
}

static void	fill_from_parts(char **parts, int *out, int *out_index)
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

static void	fill_numbers(int argc, char *argv[], int *out)
{
	int		out_index;
	int		i;
	char	**parts;

	out_index = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_strchr(argv[i], CH_SPACE))
		{
			parts = ft_split(argv[i], CH_SPACE);
			fill_from_parts(parts, out, &out_index);
		}
		else
		{
			store_token(argv[i], out, &out_index, NULL);
		}
		i++;
	}
}

static bool	has_duplicates(int *arr, int n)
{
    if (n < 2)
        return false;

    ft_heap_sort(arr, n);
	size_t i = 1;
    while (i < n) {
        if (arr[i] == arr[i - 1])
            return true;
		i++;
    }
	return (false);
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
	if (has_duplicates(buf, total))
		fatal_cleanup_and_exit(buf, NULL);
	res.input = buf;
	res.count = total;
	return (res);
}
