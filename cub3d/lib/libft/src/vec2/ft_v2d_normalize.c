#include "vec2.h"

t_v2d	ft_v2d_normalize(t_v2d vector)
{
	double	length;

	length = ft_v2d_length(vector);
	if (length == 0.0)
		return ((t_v2d){0.0, 0.0});
	return (ft_v2d_scale(vector, 1.0 / length));
}
