/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:45:49 by ptison            #+#    #+#             */
/*   Updated: 2025/08/19 20:45:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOI_H
# define FT_STRTOI_H

struct				s_parse_result
{
	unsigned int	accumulated_value;
	int				overflow_detected;
	int				digits_found;
};

int					ft_strtoi10(const char *nptr, char **endptr);

#endif
