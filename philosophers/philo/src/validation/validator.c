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
#include <stdbool.h>

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

static bool	parse_core_arguments(char **av, t_inputs *inputs)
{
	int	temp;

	temp = parse_positive_int(av[1]);
	if (temp == -1)
		return (false);
	inputs->nb_philos = (unsigned int)temp;
	temp = parse_positive_int(av[2]);
	if (temp == -1)
		return (false);
	inputs->time_to_die = temp;
	temp = parse_positive_int(av[3]);
	if (temp == -1)
		return (false);
	inputs->time_to_eat = temp;
	temp = parse_positive_int(av[4]);
	if (temp == -1)
		return (false);
	inputs->time_to_sleep = temp;
	return (true);
}

static bool	parse_optional_argument(int ac, char **av, t_inputs *inputs)
{
	if (ac == 6)
	{
		int	temp;

		temp = parse_positive_int(av[5]);
		if (temp == -1)
			return (false);
		inputs->must_eat_count = (unsigned int)temp;
		inputs->have_eat_count = true;
	}
	else
		inputs->have_eat_count = false;
	return (true);
}

static bool	parse_arguments(int ac, char **av, t_inputs *inputs)
{
	if (!parse_core_arguments(av, inputs))
		return (false);
	if (!parse_optional_argument(ac, av, inputs))
		return (false);
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
