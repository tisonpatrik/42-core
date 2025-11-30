#include "../include/validator.h"
#include "../include/simulator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[]) {
  t_inputs inputs;
  t_context* context;
  t_philosopher* philosophers;
  if (ac < 5) {
    printf("Error, too few arguments\n");
    exit(EXIT_FAILURE);
  } else if ((ac == 5) || (ac == 6)) {
    inputs = get_inputs(ac, av);
  } else {
    printf("Error, too much arguments\n");
    exit(EXIT_FAILURE);
  }
  context = create_context(inputs);
  if (!context)
  {
    printf("Error, failed to create context\n");
    exit(EXIT_FAILURE);
  }
  philosophers = create_philosophers(context, inputs);
  if (!philosophers)
  {
    printf("Error, failed to create philosophers\n");
    destroy_context(context);
    exit(EXIT_FAILURE);
  }
  run_simulation(context, philosophers);
  destroy_philosophers(philosophers, inputs.count_of_philosophers);
  destroy_context(context);
  return (EXIT_SUCCESS);
}
