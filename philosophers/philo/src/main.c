#include "../include/validator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[]) {
  t_inputs inputs;

  if (ac < 5) {
    printf("Error, too few arguments\n");
    exit(EXIT_FAILURE);
  } else if ((ac == 5) || (ac == 6)) {
    inputs = get_inputs(ac, av);
  } else {
    printf("Error, too much arguments\n");
    exit(EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
