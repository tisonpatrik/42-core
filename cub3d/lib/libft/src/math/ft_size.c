#include "ft_math.h"
#include <stdint.h>

bool	ft_size_add(size_t a, size_t b, size_t *result)
{
	if (!result || a > SIZE_MAX - b)
		return (false);
	*result = a + b;
	return (true);
}

bool	ft_size_mul(size_t a, size_t b, size_t *result)
{
	if (!result || (b != 0 && a > SIZE_MAX / b))
		return (false);
	*result = a * b;
	return (true);
}
