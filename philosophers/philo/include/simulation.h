#ifndef SIMULATION_H
#define SIMULATION_H

# include "table.h"
# include "philosophy.h"
# include "validation.h"

typedef struct s_simulation
{
    t_table         table;
    t_philosopher         **philos;
    pthread_t       grim_reaper;
}   t_simulation;

typedef struct s_result
{
    t_simulation    *simulation;
    bool            ok;
}   t_result;


void	sim_start_delay(time_t start_time);
void *grim_reaper(void *data);
t_result        create_simulation(t_inputs inputs);
void            destroy_simulation(t_simulation *sim);
char            *start_simulation(t_simulation *sim);
void            stop_simulation(t_simulation *sim);
time_t          get_time_in_ms(void);

#endif
