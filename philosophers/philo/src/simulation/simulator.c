#include "../../include/simulation.h"

char *start_simulation(t_simulation *sim)
{
    unsigned int i;

    // Nastavíme start time do tabulky
    sim->table.start_time = get_time_in_ms() + (sim->table.nb_philos * 2 * 10);

    // 1. Start Philosophers
    i = 0;
    while (i < sim->table.nb_philos)
    {
        if (pthread_create(&sim->philos[i]->thread, NULL,
                &do_philosophy, sim->philos[i]) != 0)
            return ("Thread creation failed");
        i++;
    }

    // 2. Start Grim Reaper (pokud je více než 1 filozof)
    if (sim->table.nb_philos > 1)
    {
        if (pthread_create(&sim->grim_reaper, NULL,
                &grim_reaper, sim) != 0)
            return ("Thread creation failed");
    }
    return (NULL);
}

void stop_simulation(t_simulation *sim)
{
    unsigned int i;

    // 1. Join Philosophers
    i = 0;
    while (i < sim->table.nb_philos)
    {
        pthread_join(sim->philos[i]->thread, NULL);
        i++;
    }

    // 2. Join Reaper
    if (sim->table.nb_philos > 1)
        pthread_join(sim->grim_reaper, NULL);

    // 3. Print Meal Statistics (volitelné)
    if (sim->table.must_eat_count != -1)
    {
        unsigned int full_count = 0;
        i = 0;
        while (i < sim->table.nb_philos)
        {
            if (sim->philos[i]->times_ate >= (unsigned int)sim->table.must_eat_count)
                full_count++;
            i++;
        }
        printf("%d/%d philosophers had at least %d meals.\n",
            full_count, sim->table.nb_philos, sim->table.must_eat_count);
    }
}
