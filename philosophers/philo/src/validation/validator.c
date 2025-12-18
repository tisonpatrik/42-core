/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:53:21 by ptison            #+#    #+#             */
/*   Updated: 2025/12/18 13:53:32 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/validation.h"

static bool	are_values_valid(t_inputs inp)
{
	if (inp.nb_philos > MAX_PHILOS)
		return (false);
	if (inp.time_to_die < MIN_TIME_MS || inp.time_to_eat < MIN_TIME_MS
		|| inp.time_to_sleep < MIN_TIME_MS)
	{
		return (false);
	}
	return (true);
}

static bool	parse_arguments(int ac, char **av, t_inputs *inputs)
{
	inputs->nb_philos = parse_positive_int(av[1]);
	inputs->time_to_die = parse_positive_int(av[2]);
	inputs->time_to_eat = parse_positive_int(av[3]);
	inputs->time_to_sleep = parse_positive_int(av[4]);
	if (ac == 6)
		inputs->must_eat_count = parse_positive_int(av[5]);
	else
		inputs->must_eat_count = -1;
	if (inputs->nb_philos == -1 || inputs->time_to_die == -1
		|| inputs->time_to_eat == -1 || inputs->time_to_sleep == -1 || (ac == 6
			&& inputs->must_eat_count == -1))
	{
		return (false);
	}
	return (true);
}

t_parsed	inputs_validator(int ac, char **av)
{
	t_parsed	result;

	result.ok = false;
	if (ac < 5 || ac > 6)
		return (result);
	if (!parse_arguments(ac, av, &result.inputs))
		return (result);
	if (!are_values_valid(result.inputs))
		return (result);
	result.ok = true;
	return (result);
}
