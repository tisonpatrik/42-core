package solver

import (
	"push_swap_prototype/internal/stack"
)

// ChunkValue returns the value at position n in the chunk
// Equivalent to chunk_value in C implementation
func ChunkValue(ps *stack.PushSwapData, chunk *stack.Chunk, n int) int {
	if chunk == nil || n <= 0 || n > chunk.Size {
		return 0
	}
	
	stk := locToStack(ps, chunk.Loc)
	if stk == nil {
		return 0
	}
	
	var i int
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
		for j := 1; j < n; j++ {
			i = stk.NextDown(i)
		}
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
		for j := 1; j < n; j++ {
			i = stk.NextUp(i)
		}
	default:
		i = stk.GetTop() // Default fallback like C
	}
	
	// FIXED: Remove bounds check to match C implementation exactly
	// C doesn't have bounds checking, so Go shouldn't either
	return stk.GetStack()[i]
}

// ChunkMaxValue returns the maximum value in the chunk
// Equivalent to chunk_max_value in C implementation
func ChunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {
	if chunk == nil || chunk.Size <= 0 {
		return 0
	}
	
	stk := locToStack(ps, chunk.Loc)
	if stk == nil {
		return 0
	}
	
	var i int
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop() // Default fallback like C
	}
	
	maxVal := 0 // Initialize to 0 like C implementation
	
	for j := 0; j < chunk.Size; j++ {
		if stk.GetStack()[i] > maxVal {
			maxVal = stk.GetStack()[i]
		}
		
		// Move to next element based on location
		switch chunk.Loc {
		case stack.TOP_A, stack.TOP_B:
			i = stk.NextDown(i)
		case stack.BOTTOM_A, stack.BOTTOM_B:
			i = stk.NextUp(i)
		}
	}
	
	return maxVal
}

// locToStack returns the appropriate stack based on the location
func locToStack(ps *stack.PushSwapData, loc stack.Loc) *stack.Stack {
	if loc == stack.TOP_A || loc == stack.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}