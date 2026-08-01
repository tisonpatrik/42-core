#include "prng.h"
#include <stdint.h>

#define LCG_MULTIPLIER 1664525U
#define LCG_INCREMENT 1013904223U

t_prng	ft_prng_create(uint32_t seed)
{
	return ((t_prng){seed});
}

uint32_t	ft_prng_next(t_prng *prng)
{
	if (!prng)
		return (0);
	prng->state = prng->state * LCG_MULTIPLIER + LCG_INCREMENT;
	return (prng->state);
}

static size_t	prng_next_size(t_prng *prng)
{
	size_t	value;

	value = ft_prng_next(prng);
	if (sizeof(size_t) > sizeof(uint32_t))
	{
		value *= (size_t)UINT32_MAX + 1;
		value += ft_prng_next(prng);
	}
	return (value);
}

size_t	ft_prng_bounded(t_prng *prng, size_t upper_bound)
{
	size_t	value;
	size_t	threshold;

	if (!prng || upper_bound == 0)
		return (0);
	threshold = (SIZE_MAX % upper_bound + 1) % upper_bound;
	value = prng_next_size(prng);
	while (value < threshold)
		value = prng_next_size(prng);
	return (value % upper_bound);
}
