#include "color.h"

void	ft_rgba_fill(t_rgba_ref destination, size_t count, t_rgba color)
{
	while (count > 0)
	{
		destination.bytes[0] = color.red;
		destination.bytes[1] = color.green;
		destination.bytes[2] = color.blue;
		destination.bytes[3] = color.alpha;
		destination.bytes += FT_RGBA_CHANNEL_COUNT;
		count--;
	}
}
