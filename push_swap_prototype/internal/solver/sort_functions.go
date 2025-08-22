package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// sortThree sorts three elements in a chunk
func sortThree(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("    sortThree: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	switch chunk.Loc {
	case stack.TOP_A:
		fmt.Printf("      sortThreeTopA\n")
		sortThreeTopA(ps, chunk)
	case stack.BOTTOM_A:
		fmt.Printf("      sortThreeBottomA\n")
		sortThreeBottomA(ps, chunk)
	case stack.TOP_B:
		fmt.Printf("      sortThreeTopB\n")
		sortThreeTopB(ps, chunk)
	case stack.BOTTOM_B:
		fmt.Printf("      sortThreeBottomB\n")
		sortThreeBottomB(ps, chunk)
	}
	
	fmt.Printf("    After sortThree: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
}

// sortThreeTopA sorts three elements when chunk is at TOP_A
func sortThreeTopA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("        sortThreeTopA: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	// If we're already at TOP_A and sorting 3 elements, use the simple sort_three_a logic
	if chunk.Loc == stack.TOP_A && chunk.Size == 3 {
		fmt.Printf("          Using simple sort_three_a logic\n")
		
		// Use 1-based indexing like C implementation
		first := ps.A.GetValueAtPosition(1)
		second := ps.A.GetValueAtPosition(2)
		third := ps.A.GetValueAtPosition(3)
		
		fmt.Printf("          Values: first=%d, second=%d, third=%d\n", first, second, third)
		
		// Apply the same logic as C implementation
		if first > second && third > second && third > first {
			// Case: first > second, third > second, third > first
			fmt.Printf("          Case 1: Swap_a\n")
			stack.Swap_a(ps)
		} else if first > second && third > second && first > third {
			// Case: first > second, third > second, first > third  
			fmt.Printf("          Case 2: Rotate_a\n")
			stack.Rotate_a(ps)
		} else if second > first && second > third && first > third {
			// Case: second > first, second > third, first > third
			fmt.Printf("          Case 3: R_rotate_a\n")
			stack.R_rotate_a(ps)
		} else if second > first && second > third && third > first {
			// Case: second > first, second > third, third > first
			fmt.Printf("          Case 4: Swap_a + Rotate_a\n")
			stack.Swap_a(ps)
			stack.Rotate_a(ps)
		} else if first > second && second > third && first > third {
			// Case: first > second, second > third, first > third
			fmt.Printf("          Case 5: Swap_a + R_rotate_a\n")
			stack.Swap_a(ps)
			stack.R_rotate_a(ps)
		}
		
		// Chunk is sorted, but don't modify size (like C implementation)
		fmt.Printf("          Simple sort complete, returning\n")
		return
	}
	
	fmt.Printf("          Using chunk-based sorting logic\n")
	
	// For chunk-based sorting, use the original logic with max value
	stk := ps.A
	max := chunkMaxValue(ps, chunk)
	
	fmt.Printf("          Max value: %d\n", max)
	
	// Use 1-based indexing like C implementation
	if stk.GetValueAtPosition(1) == max {
		fmt.Printf("          A[0] == max, executing: Swap_a + Rotate_a + Swap_a + R_rotate_a\n")
		stack.Swap_a(ps)
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	} else if stk.GetValueAtPosition(2) == max {
		fmt.Printf("          A[1] == max, executing: Rotate_a + Swap_a + R_rotate_a\n")
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	}
	
	// Update chunk location and size exactly like C
	fmt.Printf("          Updating chunk: loc=TOP_A, size-=1\n")
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeTopB sorts three elements when chunk is at TOP_B
func sortThreeTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("        sortThreeTopB: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	stack.Push_a(ps)
	fmt.Printf("          Executed: Push_a\n")
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		fmt.Printf("          B[0] == max, executing: Push_a + Swap_a\n")
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else if ps.B.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		fmt.Printf("          B[1] == max, executing: Swap_b + Push_a + Swap_a\n")
		stack.Swap_b(ps)
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else {
		fmt.Printf("          B[2] == max, executing: Push_a\n")
		stack.Push_a(ps)
	}
	
	stack.Push_a(ps)
	fmt.Printf("          Executed: Push_a\n")
	
	// Update chunk location and size exactly like C
	fmt.Printf("          Updating chunk: loc=TOP_A, size-=1\n")
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeBottomA sorts three elements when chunk is at BOTTOM_A
func sortThreeBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("        sortThreeBottomA: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	stack.R_rotate_a(ps)
	fmt.Printf("          Executed: R_rotate_a\n")
	
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		fmt.Printf("          A[0] == max, executing: Swap_a + Rotate_a + Swap_a + R_rotate_a\n")
		stack.Swap_a(ps)
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	} else if ps.A.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		fmt.Printf("          A[1] == max, executing: Rotate_a + Swap_a + R_rotate_a\n")
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	}
	
	// Update chunk location and size exactly like C
	fmt.Printf("          Updating chunk: loc=TOP_A, size-=1\n")
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}

// sortThreeBottomB sorts three elements when chunk is at BOTTOM_B
func sortThreeBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("        sortThreeBottomB: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	stack.R_rotate_b(ps)
	fmt.Printf("          Executed: R_rotate_b\n")
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == chunkMaxValue(ps, chunk) {
		fmt.Printf("          B[0] == max, executing: Push_a + Swap_a\n")
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else if ps.B.GetValueAtPosition(2) == chunkMaxValue(ps, chunk) {
		fmt.Printf("          B[1] == max, executing: Swap_b + Push_a + Swap_a\n")
		stack.Swap_b(ps)
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else {
		fmt.Printf("          B[2] == max, executing: Push_a\n")
		stack.Push_a(ps)
	}
	
	stack.Push_a(ps)
	fmt.Printf("          Executed: Push_a\n")
	
	// Update chunk location and size exactly like C
	fmt.Printf("          Updating chunk: loc=TOP_A, size-=1\n")
	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	sortTwo(ps, chunk)
}


