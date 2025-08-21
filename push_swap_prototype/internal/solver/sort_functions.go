package solver

import "push_swap_prototype/internal/stack"

// sortThree sorts three elements in a chunk
func sortThree(ps *stack.PushSwapData, chunk *stack.Chunk) {
	switch chunk.Loc {
	case stack.TOP_A:
		sortThreeTopA(ps, chunk)
	case stack.BOTTOM_A:
		sortThreeBottomA(ps, chunk)
	case stack.TOP_B:
		sortThreeTopB(ps, chunk)
	case stack.BOTTOM_B:
		sortThreeBottomB(ps, chunk)
	}
}

// sortThreeTopA sorts three elements when chunk is at TOP_A
func sortThreeTopA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	// If we're already at TOP_A and sorting 3 elements, use the simple sort_three_a logic
	if chunk.Loc == stack.TOP_A && chunk.Size == 3 {
		// Use 1-based indexing like C implementation
		first := ps.A.GetValueAtPosition(1)
		second := ps.A.GetValueAtPosition(2)
		third := ps.A.GetValueAtPosition(3)
		
		// Apply the same logic as C implementation
		if first > second && third > second && third > first {
			// Case: first > second, third > second, third > first
			stack.Swap_a(ps)
		} else if first > second && third > second && first > third {
			// Case: first > second, third > second, first > third  
			stack.Rotate_a(ps)
		} else if second > first && second > third && first > third {
			// Case: second > first, second > third, first > third
			stack.R_rotate_a(ps)
		} else if second > first && second > third && third > first {
			// Case: second > first, second > third, third > first
			stack.Swap_a(ps)
			stack.Rotate_a(ps)
		} else if first > second && second > third && first > third {
			// Case: first > second, second > third, first > third
			stack.Swap_a(ps)
			stack.R_rotate_a(ps)
		}
		
		// Chunk is sorted, but don't modify size (like C implementation)
		return
	}
	
	// For chunk-based sorting, use the original logic with max value
	stk := ps.A
	max := chunkMaxValue(ps, chunk)
	
	// Use 1-based indexing like C implementation
	if stk.GetValueAtPosition(1) == max {
		stack.Swap_a(ps)
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	} else if stk.GetValueAtPosition(2) == max {
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	}
	
	// Update chunk location and size exactly like C
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeTopB sorts three elements when chunk is at TOP_B
func sortThreeTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.Push_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else if ps.B.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		stack.Swap_b(ps)
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else {
		stack.Push_a(ps)
	}
	
	stack.Push_a(ps)
	
	// Update chunk location and size exactly like C
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeBottomA sorts three elements when chunk is at BOTTOM_A
func sortThreeBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	} else if ps.A.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		stack.R_rotate_a(ps)
	} else {
		stack.Push_b(ps)
		stack.R_rotate_a(ps)
		stack.Swap_a(ps)
		stack.Push_a(ps)
	}
	
	// Update chunk location and size exactly like C	
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeBottomB sorts three elements when chunk is at BOTTOM_B
func sortThreeBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		stack.Push_a(ps)
		stack.R_rotate_b(ps)
	} else if ps.B.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		stack.Swap_b(ps)
		stack.Push_a(ps)
		stack.R_rotate_b(ps)
	} else {
		stack.R_rotate_b(ps)
		stack.Push_a(ps)
	}
	
	// Update chunk location and size exactly like C
	chunk.Loc = stack.TOP_B
	chunk.Size -= 1
	sortTwo(ps, chunk)
}


