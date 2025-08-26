package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// Equivalent to chunk_value in C implementation
func ChunkValue(ps *ops.SortingState, chunk_item *chunk.Chunk, n int) int {
	// n is the position (0-based), so we can use it directly with GetValue
	loc := chunk.GetLoc(chunk_item)
	stk := locToStack(ps, loc)
	
	// Validate position
	if n < 0 || n >= chunk.GetSize(chunk_item) {
		return stack.NullValue()
	}
	
	return stack.GetValue(stk, n)
}

// Equivalent to chunk_max_value in C implementation
func ChunkMaxValue(ps *ops.SortingState, chunk_item *chunk.Chunk) int {
	if chunk_item == nil || chunk.GetSize(chunk_item) <= 0 {
		return 0
	}
	
	stk := locToStack(ps, chunk.GetLoc(chunk_item))
	size := chunk.GetSize(chunk_item)
	maxVal := 0

	// Use positions (0-based) instead of indices for GetValue
	for j := 0; j < size; j++ {
		value := stack.GetValue(stk, j)
		if value > maxVal {
			maxVal = value
		}
	}
	
	return maxVal
}

func locToStack(ps *ops.SortingState, loc chunk.Loc) *stack.Stack {
	if loc == chunk.TOP_A || loc == chunk.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}