#include "../../include/simulation.h"

static bool init_table(t_table *table, t_inputs inputs)
{
    table->nb_philos = inputs.nb_philos;
    table->time_to_die = inputs.time_to_die;
    table->time_to_eat = inputs.time_to_eat;
    table->time_to_sleep = inputs.time_to_sleep;
    table->must_eat_count = inputs.must_eat_count;
    table->sim_stop = false;

    // 1. Init global mutexes
    if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
        return (false);
    if (pthread_mutex_init(&table->write_lock, 0) != 0)
    {
        pthread_mutex_destroy(&table->sim_stop_lock);
        return (false);
    }

    // 2. Init forks array
    table->fork_locks = init_forks(table->nb_philos);
    if (!table->fork_locks)
    {
        pthread_mutex_destroy(&table->write_lock);
        pthread_mutex_destroy(&table->sim_stop_lock);
        return (false);
    }
    return (true);
}

/*
 * create_simulation:
 * Entry point for allocation. Creates simulation -> table -> philos.
 */
t_result create_simulation(t_inputs inputs)
{
    t_simulation *sim;

    sim = malloc(sizeof(t_simulation));
    if (!sim)
        return ((t_result){NULL, false});

    // 1. Setup shared table (mutexes, forks)
    if (!init_table(&sim->table, inputs))
    {
        free(sim);
        return ((t_result){NULL, false});
    }

    // 2. Create philosophers
    sim->philos = init_philosophers(&sim->table);
    if (!sim->philos)
    {
        // Rollback table init
        destroy_forks(sim->table.fork_locks, sim->table.nb_philos);
        pthread_mutex_destroy(&sim->table.write_lock);
        pthread_mutex_destroy(&sim->table.sim_stop_lock);
        free(sim);
        return ((t_result){NULL, false});
    }

    return ((t_result){sim, true});
}

/*
 * destroy_simulation:
 * Clean up everything in reverse order.
 */
void destroy_simulation(t_simulation *sim)
{
    if (!sim)
        return;

    // 1. Destroy philosophers
    destroy_philosophers(sim->philos, sim->table.nb_philos);

    // 2. Destroy table resources
    destroy_forks(sim->table.fork_locks, sim->table.nb_philos);
    pthread_mutex_destroy(&sim->table.write_lock);
    pthread_mutex_destroy(&sim->table.sim_stop_lock);

    // 3. Free the main struct
    free(sim);
}
