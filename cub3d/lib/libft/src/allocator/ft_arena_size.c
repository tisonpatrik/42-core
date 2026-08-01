#include "allocator.h"
#include "ft_math.h"

void	*ft_arena_push_array(t_arena *arena, size_t count, size_t item_size)
{
	size_t	size;

	if (!ft_size_mul(count, item_size, &size))
		return (NULL);
	return (ft_arena_push(arena, size));
}

size_t	ft_arena_align_size(size_t size)
{
	size_t	alignment;
	size_t	padding;

	alignment = _Alignof(max_align_t);
	padding = alignment - 1;
	if (size == 0 || size > SIZE_MAX - padding)
		return (0);
	return ((size + padding) / alignment * alignment);
}

bool	ft_arena_measure(size_t *total, size_t count, size_t item_size)
{
	size_t	bytes;
	size_t	aligned;

	if (!total || !ft_size_mul(count, item_size, &bytes))
		return (false);
	aligned = ft_arena_align_size(bytes);
	if (aligned == 0)
		return (false);
	return (ft_size_add(*total, aligned, total));
}
