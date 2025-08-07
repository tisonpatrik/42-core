#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exit_with_error(void) {
  fprintf(stderr, "Error\n");
  return -1;
}

int validate_inputs(int count, char **av, int *inputs) {
  int i = 1;
  int pos = 0;

  while (i <= count) {
    int number = atoi(av[i]);
    if (number == 0) {
      if (strcmp(av[i], "0") != 0 && strtol(av[i], NULL, 10) == 0) {
        return 1;
      }
    }
    inputs[pos] = number;
    pos++;

    i++;
  }
  return 0;
}

int main(int ac, char **av) {
  if (ac < 2) {
    return exit_with_error();
  }

  int count = ac - 1;

  int *inputs = malloc(count * sizeof(int));
  if (inputs == NULL) {
    return exit_with_error();
  }

  if (validate_inputs(count, av, inputs) != 0) {
    return exit_with_error();
  }

  for (int i = 0; i < count; i++) {
    printf("%d ", inputs[i]);
  }
  printf("\n");

  free(inputs);
  return 0;
}
