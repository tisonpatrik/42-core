/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrik <patrik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:30:00 by patrik            #+#    #+#             */
/*   Updated: 2025/08/18 15:30:00 by patrik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOI_H
# define FT_STRTOI_H


struct s_parse_result
{
	unsigned int	accumulated_value;	
	int		overflow_detected;
	int		digits_found;		
};

int		ft_strtoi10(const char *nptr, char **endptr);

#endif
