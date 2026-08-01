#include "color.h"

t_rgba	ft_rgba_create(uint8_t red, uint8_t green, uint8_t blue,
	uint8_t alpha)
{
	return ((t_rgba){red, green, blue, alpha});
}

t_rgba_ref	ft_rgba_ref(uint8_t *bytes)
{
	return ((t_rgba_ref){bytes});
}

t_rgba	ft_rgba_read(t_rgba_ref source)
{
	return ((t_rgba){source.bytes[0], source.bytes[1],
		source.bytes[2], source.bytes[3]});
}

void	ft_rgba_write(t_rgba_ref destination, t_rgba color)
{
	destination.bytes[0] = color.red;
	destination.bytes[1] = color.green;
	destination.bytes[2] = color.blue;
	destination.bytes[3] = color.alpha;
}

void	ft_rgba_copy(t_rgba_ref destination, t_rgba_ref source)
{
	destination.bytes[0] = source.bytes[0];
	destination.bytes[1] = source.bytes[1];
	destination.bytes[2] = source.bytes[2];
	destination.bytes[3] = source.bytes[3];
}
