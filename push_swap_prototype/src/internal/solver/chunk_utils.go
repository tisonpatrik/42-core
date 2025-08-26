package solver

import (
	"push_swap_prototype/internal/stack"
)

// Equivalent to chunk_value in C implementation
func ChunkValue(ps *stack.SortingState, chunk *stack.Chunk, n int) int {

	loc := chunk.Loc
	stk := locToStack(ps, loc)

	var i int
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.Top
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.Bottom
	default:
		i = stk.Top
	}
	
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		for j := 1; j < n; j++ {
			i = stack.NextDown(stk, i)
		}
	case stack.BOTTOM_A, stack.BOTTOM_B:
		for j := 1; j < n; j++ {
			i = stack.NextUp(stk, i)
		}
	}
	return stk.Stack[i]
}

// Equivalent to chunk_max_value in C implementation
func ChunkMaxValue(ps *stack.SortingState, chunk *stack.Chunk) int {
	if chunk == nil || chunk.Size <= 0 {
		return 0
	}
	
	stk := locToStack(ps, chunk.Loc)
	size := chunk.Size
	maxVal := 0

	var i int
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.Top
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.Bottom
	default:
		i = stk.Top // Default fallback like C
	}
	
	for j := 0; j < size; j++ {
		if stk.Stack[i] > maxVal {
			maxVal = stk.Stack[i]
		}
		switch chunk.Loc {
		case stack.TOP_A, stack.TOP_B:
			i = stack.NextDown(stk, i)
		case stack.BOTTOM_A, stack.BOTTOM_B:
			i = stack.NextUp(stk, i)
		}
	}
	
	return maxVal
}

func locToStack(ps *stack.SortingState, loc stack.Loc) *stack.Stack {
	if loc == stack.TOP_A || loc == stack.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}