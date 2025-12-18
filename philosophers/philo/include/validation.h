/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:52:29 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:52:34 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

# define MAX_PHILOS 250
# define MIN_TIME_MS 60

typedef struct s_inputs
{
	unsigned int	nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	unsigned int	must_eat_count;
	bool			have_eat_count;
}					t_inputs;

typedef struct s_parsed
{
	t_inputs		inputs;
	bool			ok;
}					t_parsed;

t_parsed			inputs_validator(int ac, char **av);

int					parse_positive_int(const char *str);

#endif
