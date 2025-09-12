#include "../include/stack.h"
#include "../include/snapshot_arena.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/stack.h"

void test_snapshot_stack(void)
{
	// Arrange
    int expected_values[] = {1, 2, 3, 4, 5, 6, 7};
	t_stack *stack = create_stack();
    fill_stack(stack, expected_values, 7);
	int expected_size = 7;
	int *snapshot_values;
	int actual_size;

	// Act
    t_snapshot_arena *snapshot_arena = create_snapshot_arena();
	t_stack *empty_stack = create_stack();
	take_snapshots(snapshot_arena, stack, empty_stack);
	
	// Get snapshot data
	snapshot_values = snapshot_arena->a_values;
	actual_size = snapshot_arena->size_a;
	
	// Assert
	assert(actual_size == expected_size);
	
	// Check that snapshot contains the same elements in the same order
	for (int i = 0; i < expected_size; i++)
	{
		assert(snapshot_values[i] == expected_values[i]);
	}
	
	// Cleanup
	destroy_snapshot_arena(snapshot_arena);
	free_stack(stack);
	free_stack(empty_stack);
	
	printf("✓ snapshot_stack test passed\n");
}

