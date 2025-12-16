#ifndef VALIDATION_H
#define VALIDATION_H

# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define MAX_PHILOS 250
# define MIN_TIME_MS 100

typedef struct s_inputs
{
    int         nb_philos;
    time_t      time_to_die;
    time_t      time_to_eat;
    time_t      time_to_sleep;
    int         must_eat_count;
}   t_inputs;

typedef struct s_parsed
{
    t_inputs    inputs;
    bool        ok;
}   t_parsed;

t_parsed    inputs_validator(int ac, char **av);

int         parse_positive_int(const char *str);

#endif
