
#include "../include/simulator.h"
#include <stdlib.h>

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


/* is_valid_input:
*	Checks if all required arguments are valid, i.e. is a string of
*	digits only, which does not exceed INT MAX. Also checks if the number
*	of philosophers is valid (between 1 and MAX_PHILOS).
*	Returns true if all arguments are valid, false if one of them is invalid.
*/
bool	is_valid_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!contains_only_digits(av[i]))
			return (msg(STR_ERR_INPUT_DIGIT, av[i], false));
		nb = integer_atoi(av[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (msg(STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS, false));
		if (i != 1 && nb == -1)
			return (msg(STR_ERR_INPUT_DIGIT, av[i], false));
		i++;
	}
	return (true);
}

/* inputs_validator:
*	Validates and parses command line arguments into t_inputs struct.
*	Returns t_parsed with inputs and NULL error on success,
*	or zeroed inputs and error message on failure.
*/
t_parsed	inputs_validator(int ac, char **av)
{
	t_parsed	result;
	int			i;
	int			nb;

	result.inputs.nb_philos = 0;
	result.inputs.time_to_die = 0;
	result.inputs.time_to_eat = 0;
	result.inputs.time_to_sleep = 0;
	result.inputs.must_eat_count = -1;
	result.error = NULL;
	if (ac < 5 || ac > 6)
	{
		result.error = "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]";
		return (result);
	}
	i = 1;
	while (i < ac)
	{
		if (!contains_only_digits(av[i]))
		{
			result.error = "Invalid input: all arguments must be positive integers.";
			return (result);
		}
		nb = integer_atoi(av[i]);
		if (nb == -1)
		{
			result.error = "Invalid input: number exceeds INT_MAX.";
			return (result);
		}
		if (i == 1)
		{
			if (nb <= 0 || nb > MAX_PHILOS)
			{
				result.error = "Invalid input: number of philosophers must be between 1 and 250.";
				return (result);
			}
			result.inputs.nb_philos = nb;
		}
		else if (i == 2)
			result.inputs.time_to_die = nb;
		else if (i == 3)
			result.inputs.time_to_eat = nb;
		else if (i == 4)
			result.inputs.time_to_sleep = nb;
		else if (i == 5)
			result.inputs.must_eat_count = nb;
		i++;
	}
	return (result);
}
