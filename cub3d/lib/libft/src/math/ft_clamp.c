#include "ft_math.h"

int	ft_max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_clamp_int(int value, int minimum, int maximum)
{
	if (value < minimum)
		return (minimum);
	if (value > maximum)
		return (maximum);
	return (value);
}

double	ft_clamp_double(double value, double minimum, double maximum)
{
	if (value < minimum)
		return (minimum);
	if (value > maximum)
		return (maximum);
	return (value);
}
