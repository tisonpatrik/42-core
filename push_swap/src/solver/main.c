/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:56:32 by ptison            #+#    #+#             */
/*   Updated: 2025/10/05 18:28:01 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/solver.h"
#include <unistd.h>

static void	handle_error(t_parser_result result)
{
	if (result.error == FAILURE)
	{
		free_parser_result(&result);
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (result.error == NO_ARGS)
	{
		free_parser_result(&result);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_parser_result	result;
	t_sorting_state	*state;

	result = parse_args(argc, argv);
	if (result.error != SUCCESS)
		handle_error(result);
	state = create_sorting_state(result.input, result.count);
	if (!state)
	{
		handle_error(result);
	}
	solve_push_swap(state);
	print_operations(state);
	free_sorting_state(state);
	free_parser_result(&result);
	return (EXIT_SUCCESS);
}
