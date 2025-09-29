/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_result.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:06:28 by ptison            #+#    #+#             */
/*   Updated: 2025/09/29 09:35:51 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validator.h"

t_parser_result	create_parser_result(int *input, int count,
		t_validation_error error)
{
	t_parser_result	result;

	result.input = input;
	result.count = count;
	result.error = error;
	return (result);
}

void	free_parser_result(t_parser_result *result)
{
	if (result && result->input)
	{
		free(result->input);
		result->input = NULL;
	}
}

t_count_of_arguments	create_count_of_arguments(int count,
		t_validation_error error)
{
	t_count_of_arguments	result;

	result.count = count;
	result.error = error;
	return (result);
}
