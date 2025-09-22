/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:35 by ptison            #+#    #+#             */
/*   Updated: 2025/09/22 18:27:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/solver.h"
#include "../include/validator.h"
#include "checker_bonus.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_parser_result	result;
	t_sorting_state	*state;
	t_list			*operations;

	result = parse_args(argc, argv);
	if (result.input == NULL)
	{
		return (1);
	}
	operations = get_operations();
	state = create_state_for_checker(result.input, result.count, operations);
	free(result.input);
	if (!state)
	{
		return (1);
	}
	check_result(state);
	free_sorting_state(state);
	return (0);
}
