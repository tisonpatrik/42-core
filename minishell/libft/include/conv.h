/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaly <student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:28:28 by ptison            #+#    #+#             */
/*   Updated: 2026/02/26 12:22:07 by omaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H

# include "core.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>

char		*ft_itoa(int n);
long long	ft_atoll_safe(const char *str, bool *error);
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
int			ft_strtoi(const char *str, bool *error);

#endif
