/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:56:32 by ptison            #+#    #+#             */
/*   Updated: 2025/08/19 21:11:06 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdlib.h>
#include <unistd.h>

t_parser_result	parse_args(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_parser_result	result;

	result = parse_args(argc, argv);
	if (result.input == NULL)
	{
		return (1);
	}
	free(result.input);
	return (0);
}
