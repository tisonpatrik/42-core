
#ifndef SNAPSHOT_ARENA_H
# define SNAPSHOT_ARENA_H

# include "../libft/include/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include "stack.h"

/**
 * Arena structure for managing stack snapshots with automatic memory management.
 * Provides a clean interface for taking snapshots without manual malloc/free.
 */
typedef struct s_snapshot_arena
{
	int		*a_values;		// Snapshot of stack A values
	int		*b_values;		// Snapshot of stack B values
	int		size_a;			// Size of stack A snapshot
	int		size_b;			// Size of stack B snapshot
}	t_snapshot_arena;

// Arena lifecycle management
t_snapshot_arena	*create_snapshot_arena(void);
void				destroy_snapshot_arena(t_snapshot_arena *arena);

// Snapshot operations
bool				take_snapshots(t_snapshot_arena *arena, t_stack *stack_a, t_stack *stack_b);
void				clear_snapshots(t_snapshot_arena *arena);


#endif
