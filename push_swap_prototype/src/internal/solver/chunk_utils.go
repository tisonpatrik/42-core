package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/stack"
)

// Equivalent to chunk_value in C implementation
func ChunkValue(ps *stack.SortingState, chunk_item *chunk.Chunk, n int) int {

	loc := chunk_item.Loc
	stk := locToStack(ps, loc)

	var i int
	switch loc {
	case chunk.TOP_A, chunk.TOP_B:
		i = stk.Top
	case chunk.BOTTOM_A, chunk.BOTTOM_B:
		i = stk.Bottom
	default:
		i = stk.Top
	}
	
	switch loc {
	case chunk.TOP_A, chunk.TOP_B:
		for j := 1; j < n; j++ {
			i = stack.NextDown(stk, i)
		}
	case chunk.BOTTOM_A, chunk.BOTTOM_B:
		for j := 1; j < n; j++ {
			i = stack.NextUp(stk, i)
		}
	}
	return stk.Stack[i]
}

// Equivalent to chunk_max_value in C implementation
func ChunkMaxValue(ps *stack.SortingState, chunk_item *chunk.Chunk) int {
	if chunk_item == nil || chunk_item.Size <= 0 {
		return 0
	}
	
	stk := locToStack(ps, chunk_item.Loc)
	size := chunk_item.Size
	maxVal := 0

	var i int
	switch chunk_item.Loc {
	case chunk.TOP_A, chunk.TOP_B:
		i = stk.Top
	case chunk.BOTTOM_A, chunk.BOTTOM_B:
		i = stk.Bottom
	default:
		i = stk.Top // Default fallback like C
	}
	
	for j := 0; j < size; j++ {
		if stk.Stack[i] > maxVal {
			maxVal = stk.Stack[i]
		}
		switch chunk_item.Loc {
		case chunk.TOP_A, chunk.TOP_B:
			i = stack.NextDown(stk, i)
		case chunk.BOTTOM_A, chunk.BOTTOM_B:
			i = stack.NextUp(stk, i)
		}
	}
	
	return maxVal
}

func locToStack(ps *stack.SortingState, loc chunk.Loc) *stack.Stack {
	if loc == chunk.TOP_A || loc == chunk.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}