/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:56:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/28 22:10:11 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/solver.h"


static void	handle_validation_error(t_parser_result result)
{

	free_parser_result(&result);
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_parser_result	result;
	t_sorting_state	*state;

	result = parse_args(argc, argv);
	if (result.error != SUCCESS)
		handle_validation_error(result);
	state = create_sorting_state(result.input, result.count);
	if (!state)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	solve_push_swap(state);
	print_operations(state);
	free_sorting_state(state);
	return (EXIT_SUCCESS);
}