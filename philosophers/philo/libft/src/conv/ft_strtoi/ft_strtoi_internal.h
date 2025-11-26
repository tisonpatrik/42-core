/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:33:48 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:35 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOI_INTERNAL_H
# define FT_STRTOI_INTERNAL_H

# include "../../../include/conv.h"
# include "../../../include/core.h"
# include <errno.h>
# include <limits.h>

typedef struct s_parse_result
{
	unsigned int	accumulated_value;
	int				overflow_detected;
	int				digits_found;
}					t_parse_result;

unsigned int		calculate_cutoff(int is_negative);
unsigned int		calculate_cutlim(unsigned int *cutoff_value);
void				set_endptr(char **end_pointer,
						const char *original_string_start,
						const char *current_position, int digits_found);
int					would_overflow(unsigned int current_accumulated,
						unsigned int overflow_threshold,
						unsigned int last_digit_limit,
						unsigned int current_digit);
int					handle_overflow(int is_negative);

#endif
