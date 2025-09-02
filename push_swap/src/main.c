/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:56:32 by ptison            #+#    #+#             */
/*   Updated: 2025/09/02 13:37:51 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/validator.h"
#include <stdlib.h>
#include <unistd.h>


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
