
#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <errno.h>
#include <stdbool.h>

typedef struct s_inputs {
  int count_of_philosophers;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_times_each_philosopher_must_eat;
  bool is_restricted;
} t_inputs;

t_inputs get_inputs(int count, char *arguments[]);
#endif
