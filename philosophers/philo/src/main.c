
#include "../include/simulator.h"

static t_simulation	*initialize_simulation(int ac, char **av)
{
	t_parsed	parsed;
	t_result	result;

	parsed = inputs_validator(ac, av);
	if (!parsed.ok)
	{
		printf("Error\n");
		return (NULL);
	}
	result = create_simulation(parsed.inputs);
	if (!result.ok)
	{
		printf("Error\n");
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
	destroy_simulation(simulation);
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
