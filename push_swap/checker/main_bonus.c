/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:27:35 by ptison            #+#    #+#             */
/*   Updated: 2025/09/23 18:58:39 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/validator.h"
#include "checker_bonus.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	t_parser_result	result;
	t_checker_state	*state;
	t_list			*operations;

	result = parse_args(argc, argv);
	if (result.input == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	operations = get_operations();
	if (!operations)
	{
		free(result.input);
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	state = create_state_for_checker(result.input, result.count, operations);
	free(result.input);
	if (!state)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	check_result(state);
	free_checker_state(state);
	return (0);
}
