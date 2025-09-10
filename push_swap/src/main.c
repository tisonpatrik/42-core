/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:56:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/10 21:11:19 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ops.h"
#include "../include/solver.h"
#include "../include/validator.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_parser_result	result;
	t_sorting_state	*state;

	result = parse_args(argc, argv);
	if (result.input == NULL)
	{
		return (1);
	}
	free(result.input);
	state = create_sorting_state(result.input, result.count);
	solve_push_swap(state);
	free_sorting_state(state);
	return (0);
}
