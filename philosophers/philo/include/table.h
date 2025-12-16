#ifndef TABLE_H
#define TABLE_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct s_table
{
    unsigned int    nb_philos;
    time_t          time_to_die;
    time_t          time_to_eat;
    time_t          time_to_sleep;
    int             must_eat_count;
    time_t          start_time;

    bool            sim_stop;
    pthread_mutex_t sim_stop_lock;
    pthread_mutex_t write_lock;
    pthread_mutex_t *fork_locks;    // Pole zámků vidliček
}   t_table;

#endif
