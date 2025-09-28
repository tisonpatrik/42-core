/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:28:18 by ptison            #+#    #+#             */
/*   Updated: 2025/09/28 15:03:47 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "../libft/include/libft.h"
# include <stdlib.h>
# include <errno.h>

# define CH_SPACE ' '

typedef struct s_parser_result
{
	int			*input;
	int			count;
}				t_parser_result;

void			fatal_cleanup_and_exit(int *buf, char **tmp);

int				*indexize_array(const int *values, int n);
int	get_count_of_arguments(int argc, char *argv[]);
t_parser_result	parse_args(int argc, char *argv[]);

#endif
