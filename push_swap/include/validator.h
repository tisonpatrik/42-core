/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:28:18 by ptison            #+#    #+#             */
/*   Updated: 2025/10/09 16:52:58 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <limits.h>
# include <stdlib.h>

# define CH_SPACE ' '

typedef enum e_validation_status
{
	SUCCESS = 0,
	FAILURE,
	NO_ARGS,
}						t_validation_status;

typedef struct s_count_of_arguments
{
	int					count;
	t_validation_status	error;
}						t_count_of_arguments;

typedef struct s_parser_result
{
	int					*input;
	int					count;
	t_validation_status	error;
}						t_parser_result;

int						*indexize_array(const int *values, int n);
t_count_of_arguments	get_count_of_arguments(int argc, char *argv[]);
t_parser_result			parse_args(int argc, char *argv[]);

t_parser_result			create_parser_result(int *input, int count,
							t_validation_status error);
void					free_parser_result(t_parser_result *result);

t_count_of_arguments	create_count_of_arguments(int count,
							t_validation_status error);

bool					fill_numbers(int argc, char *argv[], int *out);
#endif
