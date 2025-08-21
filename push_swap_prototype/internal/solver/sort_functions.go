package solver

import (
	"push_swap_prototype/internal/operations"
)

// sortOne handles a single element in a chunk
func sortOne(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// Move element to TOP_A if it's not already there
	if chunk.Loc == operations.BOTTOM_A || chunk.Loc == operations.BOTTOM_B || chunk.Loc == operations.TOP_B {
		switch chunk.Loc {
		case operations.BOTTOM_A:
			operations.R_rotate_a(ps)
		case operations.BOTTOM_B:
			operations.R_rotate_b(ps) // Bring bottom element to top
			operations.Push_a(ps)     // Push top element to A
		case operations.TOP_B:
			operations.Push_a(ps)
		}
	}
	
	chunk.Size--
}

// sortTwo sorts two elements in a chunk
func sortTwo(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// Move elements to TOP_A if they're not already there (exactly like C implementation)
	if chunk.Loc == operations.BOTTOM_A || chunk.Loc == operations.BOTTOM_B || chunk.Loc == operations.TOP_B {
		moveFromTo(ps, chunk.Loc, operations.TOP_A)
		moveFromTo(ps, chunk.Loc, operations.TOP_A)
	}
	
	// If the top element is greater than the second element, swap them
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) > ps.A.GetValueAtPosition(2) {
		operations.Swap_a(ps)
	}
	
	chunk.Size -= 2
}

// sortThree sorts three elements in a chunk
func sortThree(ps *operations.PushSwapData, chunk *operations.Chunk) {
	switch chunk.Loc {
	case operations.TOP_A:
		sortThreeTopA(ps, chunk)
	case operations.BOTTOM_A:
		sortThreeBottomA(ps, chunk)
	case operations.TOP_B:
		sortThreeTopB(ps, chunk)
	case operations.BOTTOM_B:
		sortThreeBottomB(ps, chunk)
	}
}

// sortThreeTopA sorts three elements when chunk is at TOP_A
func sortThreeTopA(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// If we're already at TOP_A and sorting 3 elements, use the simple sort_three_a logic
	if chunk.Loc == operations.TOP_A && chunk.Size == 3 {
		// Use 1-based indexing like C implementation
		first := ps.A.GetValueAtPosition(1)
		second := ps.A.GetValueAtPosition(2)
		third := ps.A.GetValueAtPosition(3)
		
		// Apply the same logic as C implementation
		if first > second && third > second && third > first {
			// Case: first > second, third > second, third > first
			operations.Swap_a(ps)
		} else if first > second && third > second && first > third {
			// Case: first > second, third > second, first > third  
			operations.Rotate_a(ps)
		} else if second > first && second > third && first > third {
			// Case: second > first, second > third, first > third
			operations.R_rotate_a(ps)
		} else if second > first && second > third && third > first {
			// Case: second > first, second > third, third > first
			operations.Swap_a(ps)
			operations.Rotate_a(ps)
		} else if first > second && second > third && first > third {
			// Case: first > second, second > third, first > third
			operations.Swap_a(ps)
			operations.R_rotate_a(ps)
		}
		
		// Chunk is sorted, but don't modify size (like C implementation)
		return
	}
	
	// For chunk-based sorting, use the original logic with max value
	stk := ps.A
	max := chunkMaxValue(ps, chunk)
	
	// Use 1-based indexing like C implementation
	if stk.GetValueAtPosition(1) == max {
		operations.Swap_a(ps)
		operations.Rotate_a(ps)
		operations.Swap_a(ps)
		operations.R_rotate_a(ps)
	} else if stk.GetValueAtPosition(2) == max {
		operations.Rotate_a(ps)
		operations.Swap_a(ps)
		operations.R_rotate_a(ps)
	}
	
	// Update chunk location and size exactly like C
	chunk.Loc = operations.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeTopB sorts three elements when chunk is at TOP_B
func sortThreeTopB(ps *operations.PushSwapData, chunk *operations.Chunk) {
	operations.Push_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		operations.Push_a(ps)
		operations.Swap_a(ps)
	} else if ps.B.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		operations.Swap_b(ps)
		operations.Push_a(ps)
		operations.Swap_a(ps)
	} else {
		operations.Push_a(ps)
	}
	
	operations.Push_a(ps)
	
	// Update chunk location and size exactly like C
	chunk.Loc = operations.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeBottomA sorts three elements when chunk is at BOTTOM_A
func sortThreeBottomA(ps *operations.PushSwapData, chunk *operations.Chunk) {
	operations.R_rotate_a(ps)
	operations.R_rotate_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		operations.Swap_a(ps)
		operations.R_rotate_a(ps)
	} else if ps.A.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		operations.R_rotate_a(ps)
	} else {
		operations.Push_b(ps)
		operations.R_rotate_a(ps)
		operations.Swap_a(ps)
		operations.Push_a(ps)
	}
	
	// Update chunk location and size exactly like C
	chunk.Loc = operations.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeBottomB sorts three elements when chunk is at BOTTOM_B
func sortThreeBottomB(ps *operations.PushSwapData, chunk *operations.Chunk) {
	operations.R_rotate_b(ps)
	operations.R_rotate_b(ps)
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		operations.Push_a(ps)
		operations.R_rotate_b(ps)
	} else if ps.B.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		operations.Swap_b(ps)
		operations.Push_a(ps)
		operations.R_rotate_b(ps)
	} else {
		operations.R_rotate_b(ps)
		operations.Push_a(ps)
	}
	
	// Update chunk location and size exactly like C
	chunk.Loc = operations.TOP_B
	chunk.Size -= 1
	sortTwo(ps, chunk)
}


