/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prng.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:37:45 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:37:46 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRNG_H
# define PRNG_H

# include <stddef.h>
# include <stdint.h>

typedef struct s_prng
{
	uint32_t	state;
}	t_prng;

t_prng		ft_prng_create(uint32_t seed);
uint32_t	ft_prng_next(t_prng *prng);
size_t		ft_prng_bounded(t_prng *prng, size_t upper_bound);

#endif
