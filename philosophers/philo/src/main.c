
#include "../include/simulator.h"

static t_simulation	*initialize_simulation(int ac, char **av)
{
	t_parsed	parsed;
	t_result	result;

	parsed = inputs_validator(ac, av);
	if (parsed.error)
	{
		printf("Error: %s\n", parsed.error);
		return (NULL);
	}
	result = create_simulation(parsed.inputs);
	if (result.error)
	{
		printf("Error: %s\n", result.error);
		return (NULL);
	}
	return (result.simulation);
}

static void	run_simulation(t_simulation *simulation)
{
	char	*error;

	error = start_simulation(simulation);
	if (error)
	{
		printf("Error: %s\n", error);
		destroy_simulation(simulation);
		return ;
	}
	stop_simulation(simulation);
}

int	main(int ac, char **av)
{
	t_simulation	*simulation;

	simulation = initialize_simulation(ac, av);
	if (!simulation)
		return (EXIT_FAILURE);
	run_simulation(simulation);
	return (EXIT_SUCCESS);
}
