#include "../../include/optimizer.h"

static size_t	calculate_arena_size(size_t capacity)
{
	size_t	size;

	size = sizeof(t_operation) * capacity;
	size += sizeof(t_list *) * capacity;
	size += sizeof(int) * capacity;
	size += sizeof(bool) * capacity;
	return (size);
}

static void	setup_arena_memory_layout(t_optimizer_arena *arena, size_t capacity)
{
	char	*memory;
	size_t	offset;

	memory = (char *)arena->arena_memory;
	offset = 0;
	arena->operations = (t_operation *)(memory + offset);
	offset += sizeof(t_operation) * capacity;
	arena->temp_lists = (t_list **)(memory + offset);
	offset += sizeof(t_list *) * capacity;
	arena->indices = (int *)(memory + offset);
	offset += sizeof(int) * capacity;
	arena->flags = (bool *)(memory + offset);
}

t_optimizer_arena	*create_optimizer_arena(size_t capacity)
{
	t_optimizer_arena	*arena;
	size_t				arena_size;

	if (capacity == 0)
		return (NULL);
	
	arena_size = calculate_arena_size(capacity);
	arena = malloc(sizeof(t_optimizer_arena));
	if (!arena)
		return (NULL);
	
	arena->arena_memory = malloc(arena_size);
	if (!arena->arena_memory)
	{
		free(arena);
		return (NULL);
	}
	
	arena->capacity = capacity;
	arena->used = 0;
	arena->arena_size = arena_size;
	setup_arena_memory_layout(arena, capacity);
	
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
