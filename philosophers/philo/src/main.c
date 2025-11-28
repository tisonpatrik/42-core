#include "../include/validator.h"
#include "../include/simulator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[]) {
  t_inputs inputs;
  t_simulation* simulation;
  if (ac < 5) {
    printf("Error, too few arguments\n");
    exit(EXIT_FAILURE);
  } else if ((ac == 5) || (ac == 6)) {
    inputs = get_inputs(ac, av);
  } else {
    printf("Error, too much arguments\n");
    exit(EXIT_FAILURE);
  }
  simulation = create_simulation(inputs);
  run_simulation(simulation);
  return (EXIT_SUCCESS);
}
