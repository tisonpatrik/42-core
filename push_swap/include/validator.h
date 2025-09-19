/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:24:56 by patrik            #+#    #+#             */
/*   Updated: 2025/09/19 23:23:48 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "../libft/include/libft.h"

typedef struct s_parser_result
{
	int			*input;
	int			count;
}				t_parser_result;

int				get_count_of_arguments(int argc, char *argv[]);
void			fill_from_parts(char **parts, int *out, int *out_index);
void			fill_numbers(int argc, char *argv[], int *out);
void			check_duplicates(int *arr, int n);
t_parser_result	parse_args(int argc, char *argv[]);

int				count_parts(char **parts);
void			store_token(const char *tok, int *out, int *out_index,
					char **parts_for_cleanup);

int				*indexize_array(const int *values, int n);

void			fatal_cleanup_and_exit(int *buf, char **tmp);

#endif