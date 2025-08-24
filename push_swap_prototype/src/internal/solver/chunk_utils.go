package solver

import (
	"push_swap_prototype/internal/stack"
)

func ChunkValue(ps *stack.PushSwapData, chunk *stack.Chunk, n int) int {
	loc := chunk.Loc
	stk := locToStack(ps, loc)

	// Check if stack is empty or uninitialized
	if stk == nil || stk.CurrentSize() == 0 {
		return 0
	}

	var i int

	switch loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop()
	}

	// Validate index bounds
	if i < 0 || i >= len(stk.GetStack()) {
		return 0
	}

	// Match C implementation exactly: advance by n-1 positions
	// n=1 means first element in chunk, n=2 means second element, etc.
	switch loc {
	case stack.TOP_A, stack.TOP_B:
		for n--; n > 0; n-- {
			i = stk.NextDown(i)
		}
	case stack.BOTTOM_A, stack.BOTTOM_B:
		for n--; n > 0; n-- {
			i = stk.NextUp(i)
		}
	}

	// Validate the final index
	if i < 0 || i >= len(stk.GetStack()) {
		return 0
	}

	// Get the value at the calculated index
	result := stk.GetStack()[i]
	return result
}

func ChunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {
	var stk *stack.Stack
	var size int
	var maxValue int
	var i int

	stk = locToStack(ps, chunk.Loc)
	
	// Check if stack is empty or chunk size is invalid
	if stk == nil || stk.CurrentSize() == 0 || chunk.Size <= 0 {
		return 0
	}
	
	size = chunk.Size
	
	// Fix: Start with the first value in the chunk, not 0
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop()
	}
	
	// Initialize maxValue with the first value in the chunk
	maxValue = stk.GetStack()[i]

	// Process exactly chunk_size elements
	for ; size > 0; size-- {
		if stk.GetStack()[i] > maxValue {
			maxValue = stk.GetStack()[i]
		}
		switch chunk.Loc {
		case stack.TOP_A, stack.TOP_B:
			i = stk.NextDown(i)
		case stack.BOTTOM_A, stack.BOTTOM_B:
			i = stk.NextUp(i)
		}
	}
	return maxValue
}

// ChunkMinValue finds the minimum value in a chunk (matching C implementation)
func ChunkMinValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {
	var stk *stack.Stack
	var size int
	var minValue int
	var i int

	stk = locToStack(ps, chunk.Loc)
	
	// Check if stack is empty or chunk size is invalid
	if stk == nil || stk.CurrentSize() == 0 || chunk.Size <= 0 {
		return 0
	}
	
	size = chunk.Size
	
	// Start with the first value in the chunk
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		i = stk.GetTop()
	case stack.BOTTOM_A, stack.BOTTOM_B:
		i = stk.GetBottom()
	default:
		i = stk.GetTop()
	}
	
	// Initialize minValue with the first value in the chunk
	minValue = stk.GetStack()[i]

	// Process exactly chunk_size elements
	for ; size > 0; size-- {
		if stk.GetStack()[i] < minValue {
			minValue = stk.GetStack()[i]
		}
		switch chunk.Loc {
		case stack.TOP_A, stack.TOP_B:
			i = stk.NextDown(i)
		case stack.BOTTOM_A, stack.BOTTOM_B:
			i = stk.NextUp(i)
		}
	}
	return minValue
}

// locToStack returns the appropriate stack based on the location
func locToStack(ps *stack.PushSwapData, loc stack.Loc) *stack.Stack {
	if loc == stack.TOP_A || loc == stack.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}
