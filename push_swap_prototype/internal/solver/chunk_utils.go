package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

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
	fmt.Printf("    chunkValue: chunk loc=%v, size=%d, position=%d\n", chunk.Loc, chunk.Size, n)
	
	stk := locToStack(ps, chunk.Loc)
	fmt.Printf("      Using stack: %v, stack size: %d\n", chunk.Loc, stk.Size())
	
	// Check bounds: position must be within chunk size and stack must have enough elements
	if n < 1 || n > chunk.Size || n > stk.Size() {
		fmt.Printf("      Bounds check failed: n=%d, chunk.Size=%d, stack.Size=%d\n", n, chunk.Size, stk.Size())
		return 0
	}
	
	// For our linear stack implementation, we need to handle this differently
	// TOP means from the beginning of the slice, BOTTOM means from the end
	var result int
	switch chunk.Loc {
	case stack.TOP_A, stack.TOP_B:
		// For TOP, position 1 is index 0, position 2 is index 1, etc.
		// Use 1-based indexing like C implementation
		result = stk.GetValueAtPosition(n)
		fmt.Printf("      TOP case: position %d -> index %d, value=%d\n", n, n, result)
	case stack.BOTTOM_A, stack.BOTTOM_B:
		// For BOTTOM, position 1 is the last element, position 2 is second-to-last, etc.
		// Convert to 1-based position from the bottom
		result = stk.GetValueAtPosition(stk.Size() - n + 1)
		fmt.Printf("      BOTTOM case: position %d -> index %d, value=%d\n", n, stk.Size() - n + 1, result)
	}
	
	fmt.Printf("      chunkValue result: %d\n", result)
	return result
}

// chunkMaxValue finds the maximum value in the given chunk
func chunkMaxValue(ps *stack.PushSwapData, chunk *stack.Chunk) int {
	fmt.Printf("    chunkMaxValue: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	size := chunk.Size
	maxValue := 0
	
	// Get all values in the chunk and find the maximum
	for i := 1; i <= size; i++ {
		val := chunkValue(ps, chunk, i)
		if val > maxValue {
			maxValue = val
			fmt.Printf("      New max: %d at position %d\n", maxValue, i)
		}
	}
	
	fmt.Printf("      chunkMaxValue result: %d\n", maxValue)
	return maxValue
}




