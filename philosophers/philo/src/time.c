#include "../include/simulation.h"

/* get_time_in_ms:
*	Gets the current time in miliseconds since the Epoch (1970-01-01 00:00:00).
*	Returns the time value.
*/
time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* sim_start_delay:
*	Waits for a small delay at the beginning of each threads execution
*	so that all threads start at the same time with the same start time
*	reference. This ensures the grim reaper thread is synchronized with
*	the philosopher threads.
*/
void	sim_start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}
