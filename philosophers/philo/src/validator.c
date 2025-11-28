

#include "../include/validator.h"
#include <stdbool.h>
#include <stdlib.h>

t_inputs get_inputs(int count, char *arguments[]) {
  char *endptr;
  endptr = NULL;
  errno = 0;
  int count_of_philosophers = ft_strtoi10(arguments[1], &endptr);
  int time_to_die = ft_strtoi10(arguments[2], &endptr);
  int time_to_eat = ft_strtoi10(arguments[3], &endptr);
  int time_to_sleep = ft_strtoi10(arguments[4], &endptr);
  if (*endptr != '\0' || errno == ERANGE) {
    exit(0);
  }
  t_inputs inputs;
  inputs.count_of_philosophers = count_of_philosophers;
  inputs.time_to_die = time_to_die;
  inputs.time_to_eat = time_to_eat;
  inputs.time_to_sleep = time_to_sleep;
  inputs.is_restricted = false;
  if (count == 6)
  {
      int number_of_times_each_philosopher_must_eat = ft_strtoi10(arguments[5], &endptr);
      if (*endptr != '\0' || errno == ERANGE) {
        exit(0);
      }
      inputs.number_of_times_each_philosopher_must_eat=number_of_times_each_philosopher_must_eat;
      inputs.is_restricted= true;
  }
  return inputs;
}
