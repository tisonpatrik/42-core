/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:13:12 by ptison            #+#    #+#             */
/*   Updated: 2025/09/02 12:27:18 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "ops.h"

typedef struct s_parser_result
{
	int			*input;
	int			count;
}				t_parser_result;

t_parser_result	parse_args(int argc, char *argv[]);

int				*indexize_array(const int *array, int len_of_array);
