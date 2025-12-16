#include "../include/simulator.h"

/* contains_only_digits:
*	Checks if a string contains only digits 0 - 9.
*	Returns true if the string only contains digits.
*	Returns false if the string contains a character that is not a digit.
*/
static bool	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

/* integer_atoi:
*	Converts a digit-only string into a positive integer.
*	Returns the converted number between 0 and INT MAX.
*	Returns -1 if the converted number exceeds INT MAX.
*/
int	integer_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

/* msg:
*	Writes a message to the console. Returns the provided exit number.
*	Used for error management.
*/
int	msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf("error: %s",str);
	else
		printf(str, detail);
	return (exit_no);
}

t_parsed	inputs_validator(int ac, char **av)
{
	t_parsed	result;

	result.ok = true;
	if (ac < 5 || ac > 6)
	{
		result.ok = false;
		return (result);
	}
	for (int i = 1; i < ac; i++)
	{
		if (!contains_only_digits(av[i]))
		{
			result.ok = false;
			return (result);
		}
	}
	result.inputs.nb_philos = integer_atoi(av[1]);
	result.inputs.time_to_die = integer_atoi(av[2]);
	result.inputs.time_to_eat = integer_atoi(av[3]);
	result.inputs.time_to_sleep = integer_atoi(av[4]);
	if (ac == 6)
		result.inputs.must_eat_count = integer_atoi(av[5]);
	if (result.inputs.nb_philos == -1 || result.inputs.time_to_die == -1 ||
		result.inputs.time_to_eat == -1 || result.inputs.time_to_sleep == -1 ||
		(ac == 6 && result.inputs.must_eat_count == -1))
	{
		result.ok = false;
		return (result);
	}
	if (result.inputs.nb_philos <= 0 || result.inputs.nb_philos > 250 ||
		result.inputs.time_to_die <= 0 || result.inputs.time_to_eat <= 0 ||
		result.inputs.time_to_sleep <= 0 ||
		(ac == 6 && result.inputs.must_eat_count <= 0))
	{
		result.ok = false;
		return (result);
	}
	return (result);
}