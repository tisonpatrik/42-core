/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:35 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 16:36:34 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/validator.h"
#include "checker_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static int	handle_error(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static int	parse_and_validate_input(int argc, char *argv[],
		t_parser_result *result)
{
	*result = parse_args(argc, argv);
	if (result->input == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	create_and_validate_state(t_parser_result *result,
		t_list *operations, t_checker_state **state)
{
	*state = create_state_for_checker(result->input, result->count, operations);
	if (!*state)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_parser_result	result;
	t_checker_state	*state;
	t_list			*operations;

	if (parse_and_validate_input(argc, argv, &result))
		return (handle_error());
	operations = get_operations();
	if (create_and_validate_state(&result, operations, &state))
	{
		free(result.input);
		return (handle_error());
	}
	free(result.input);
	check_result(state);
	free_checker_state(state);
	return (EXIT_SUCCESS);
}
