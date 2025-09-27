/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:35 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:30 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/validator.h"
#include "checker_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static int	handle_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}

static int	parse_and_validate_input(int argc, char *argv[],
		t_parser_result *result)
{
	*result = parse_args(argc, argv);
	if (result->input == NULL)
		return (1);
	return (0);
}

static int	create_and_validate_state(t_parser_result *result,
		t_list *operations, t_checker_state **state)
{
	*state = create_state_for_checker(result->input, result->count, operations);
	if (!*state)
		return (1);
	return (0);
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
	return (0);
}
