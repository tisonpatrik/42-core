package solver

import "push_swap_prototype/internal/stack"

// locToStack returns the appropriate stack based on the location
func locToStack(ps *stack.PushSwapData, loc stack.Loc) *stack.Stack {
	if loc == stack.TOP_A || loc == stack.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}

// chunkValue gets the value at a specific position in the chunk (1-based like C)
func chunkValue(ps *stack.PushSwapData, chunk *stack.Chunk, n int) int {
	stk := locToStack(ps, chunk.Loc)
	
	// Check bounds: position must be within chunk size and stack must have enough elements
	if n < 1 || n > chunk.Size || n > stk.Size() {
		return 0
	}
	
	// For our linear stack implementation, we need to handle this differently
	// TOP means from the beginning of the slice, BOTTOM means from the end
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		// For TOP, position 1 is index 0, position 2 is index 1, etc.
		// Use 1-based indexing like C implementation
		return stk.GetValueAtPosition(n)
	case stack.BOTTOM_A, stack.BOTTOM_B:
		// For BOTTOM, position 1 is the last element, position 2 is second-to-last, etc.
		// Convert to 1-based position from the bottom
		return stk.GetValueAtPosition(stk.Size() - n + 1)
	}
	
	return 0
}

// chunkMaxValue finds the maximum value in the given chunk
func chunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {
	size := chunk.Size
	maxValue := 0
	
	// Get all values in the chunk and find the maximum
	for i := 1; i <= size; i++ {
		val := chunkValue(ps, chunk, i)
		if val > maxValue {
			maxValue = val
		}
	}
	
	return maxValue
}




