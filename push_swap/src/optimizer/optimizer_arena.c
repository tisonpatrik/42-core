#include "../../include/optimizer.h"

t_optimizer_arena	*create_optimizer_arena(size_t capacity)
{
	t_optimizer_arena	*arena;
	size_t				arena_size;

	if (capacity == 0)
		return (NULL);
	
	arena_size = sizeof(t_operation) * capacity;
	arena = malloc(sizeof(t_optimizer_arena));
	if (!arena)
		return (NULL);
	
	arena->arena_memory = malloc(arena_size);
	if (!arena->arena_memory)
	{
		free(arena);
		return (NULL);
	}
	
	arena->operations = (t_operation *)arena->arena_memory;
	arena->capacity = capacity;
	arena->used = 0;
	arena->arena_size = arena_size;
	
	return (arena);
}

void	destroy_optimizer_arena(t_optimizer_arena *arena)
{
	if (!arena)
		return;
	
	if (arena->arena_memory)
		free(arena->arena_memory);
	free(arena);
}

t_operation	*arena_alloc_operation(t_optimizer_arena *arena)
{
	if (!arena || arena->used >= arena->capacity)
		return (NULL);
	
	return (&arena->operations[arena->used++]);
}

void	reset_optimizer_arena(t_optimizer_arena *arena)
{
	if (!arena)
		return;
	
	arena->used = 0;
}
