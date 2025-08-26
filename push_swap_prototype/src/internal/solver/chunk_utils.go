package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// Equivalent to chunk_value in C implementation
func ChunkValue(ps *ops.SortingState, chunk_item *chunk.Chunk, n int) int {

	loc := chunk_item.Loc
	stk := locToStack(ps, loc)

	var i int
	switch loc {
	case chunk.TOP_A, chunk.TOP_B:
		i = stack.GetTop(stk)
	case chunk.BOTTOM_A, chunk.BOTTOM_B:
		i = stack.GetBottom(stk)
	default:
		i = stack.GetTop(stk)
	}
	
	switch loc {
	case chunk.TOP_A, chunk.TOP_B:
		for j := 1; j < n; j++ {
			i = stack.Next(stk, i)
		}
	case chunk.BOTTOM_A, chunk.BOTTOM_B:
		for j := 1; j < n; j++ {
			i = stack.Previous(stk, i)
		}
	}
	return stack.GetValue(stk, i)
}

// Equivalent to chunk_max_value in C implementation
func ChunkMaxValue(ps *ops.SortingState, chunk_item *chunk.Chunk) int {
	if chunk_item == nil || chunk_item.Size <= 0 {
		return 0
	}
	
	stk := locToStack(ps, chunk_item.Loc)
	size := chunk_item.Size
	maxVal := 0

	var i int
	switch chunk_item.Loc {
	case chunk.TOP_A, chunk.TOP_B:
		i = stack.GetTop(stk)
	case chunk.BOTTOM_A, chunk.BOTTOM_B:
		i = stack.GetBottom(stk)
	default:
		i = stack.GetTop(stk) // Default fallback like C
	}
	
	for j := 0; j < size; j++ {
		if stack.GetValue(stk, i) > maxVal {
			maxVal = stack.GetValue(stk, i)
		}
		switch chunk_item.Loc {
		case chunk.TOP_A, chunk.TOP_B:
			i = stack.Next(stk, i)
		case chunk.BOTTOM_A, chunk.BOTTOM_B:
			i = stack.Previous(stk, i)
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