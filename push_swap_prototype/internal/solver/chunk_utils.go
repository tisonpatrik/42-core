package solver

import (
	"push_swap_prototype/internal/operations"
	"push_swap_prototype/internal/stack"
)

// locToStack returns the appropriate stack based on the location
func locToStack(ps *operations.PushSwapData, loc operations.Loc) *stack.Stack {
	if loc == operations.TOP_A || loc == operations.BOTTOM_A {
		return ps.A
	} else {
		return ps.B
	}
}

// chunkValue gets the value at a specific position in the chunk (1-based like C)
func chunkValue(ps *operations.PushSwapData, chunk *operations.Chunk, n int) int {
	stk := locToStack(ps, chunk.Loc)
	
	// Check bounds: position must be within chunk size and stack must have enough elements
	if n < 1 || n > chunk.Size || n > stk.Size() {
		return 0
	}
	
	// For our linear stack implementation, we need to handle this differently
	// TOP means from the beginning of the slice, BOTTOM means from the end
	switch chunk.Loc {
	case operations.TOP_A, operations.TOP_B:
		// For TOP, position 1 is index 0, position 2 is index 1, etc.
		return stk.GetValueAtPosition0(n - 1)
	case operations.BOTTOM_A, operations.BOTTOM_B:
		// For BOTTOM, position 1 is the last element, position 2 is second-to-last, etc.
		return stk.GetValueAtPosition0(stk.Size() - n)
	}
	
	return 0
}

// chunkMaxValue finds the maximum value in the given chunk
func chunkMaxValue(ps *operations.PushSwapData, chunk *operations.Chunk) int {
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

// aPartlySort checks if stack A is partially sorted from a given position (1-based like C)
func aPartlySort(ps *operations.PushSwapData, from int) bool {
	a := ps.A
	
	// Use 1-based indexing like C implementation	
	for i := from; i < a.Size(); i++ {
		current := a.GetValueAtPosition(i)
		next := a.GetValueAtPosition(i + 1)
		if next != 0 && next != current+1 {
			return false
		}
	}
	return true
}

// isConsecutive checks if four numbers are consecutive
func isConsecutive(a, b, c, d int) bool {
	// Sort all four numbers to check if they're consecutive
	sortFourNumbers(&a, &b, &c, &d)
	return (b-a == 1) && (c-b == 1) && (d-c == 1)
}

// sortThreeNumbers sorts three numbers in ascending order
func sortThreeNumbers(a, b, c *int) {
	if *a > *b {
		*a, *b = *b, *a
	}
	if *a > *c {
		*a, *c = *c, *a
	}
	if *b > *c {
		*b, *c = *c, *b
	}
}

// sortFourNumbers sorts four numbers in ascending order
func sortFourNumbers(a, b, c, d *int) {
	// First sort the first three numbers
	sortThreeNumbers(a, b, c)
	
	// Then insert the fourth number in the correct position
	if *d < *a {
		*a, *b, *c, *d = *d, *a, *b, *c
	} else if *d < *b {
		*b, *c, *d = *d, *b, *c
	} else if *d < *c {
		*c, *d = *d, *c
	}
	// If *d >= *c, it's already in the right position
}
