#include <pthread.h>
#include <stdlib.h>
/*
 * init_forks:
 * Allocates memory for 'count' mutexes and initializes them.
 * Returns NULL if allocation fails or mutex init fails.
 */
pthread_mutex_t *init_forks(unsigned int count)
{
    pthread_mutex_t *forks;
    unsigned int    i;

    forks = malloc(sizeof(pthread_mutex_t) * count);
    if (!forks)
        return (NULL);
    i = 0;
    while (i < count)
    {
        if (pthread_mutex_init(&forks[i], 0) != 0)
        {
            // Rollback: Destroy successfully initialized mutexes
            while (i-- > 0)
                pthread_mutex_destroy(&forks[i]);
            free(forks);
            return (NULL);
        }
        i++;
    }
    return (forks);
}

/*
 * destroy_forks:
 * Destroys all mutexes in the array and frees the memory.
 */
void destroy_forks(pthread_mutex_t *forks, unsigned int count)
{
    unsigned int i;

    if (!forks)
        return;
    i = 0;
    while (i < count)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
}
