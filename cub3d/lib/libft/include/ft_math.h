/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 18:28:41 by ptison            #+#    #+#             */
/*   Updated: 2025/09/27 11:37:36 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <stdbool.h>
# include <stddef.h>

int		ft_abs(int n);
int		ft_min_int(int a, int b);
int		ft_max_int(int a, int b);
int		ft_clamp_int(int value, int minimum, int maximum);
double	ft_clamp_double(double value, double minimum, double maximum);
bool	ft_size_add(size_t a, size_t b, size_t *result);
bool	ft_size_mul(size_t a, size_t b, size_t *result);
void	ft_swap_int(int *a, int *b);

#endif
