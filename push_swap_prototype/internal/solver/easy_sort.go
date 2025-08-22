package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// easySort applies simple sorting optimizations (exactly like C implementation)
func easySort(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("=== EASY_SORT START ===\n")
	fmt.Printf("Chunk: loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	fmt.Printf("Stack A size: %d, Stack B size: %d\n", ps.A.Size(), ps.B.Size())
	
	// Exactly like C: while (to_sort->loc != TOP_A && to_sort->size)
	for chunk.Loc != stack.TOP_A && chunk.Size != 0 {
		fmt.Printf("Easy sort loop - chunk loc: %v, size: %d\n", chunk.Loc, chunk.Size)
		
		// Check if chunk still has enough elements
		if chunk.Size < 1 {
			break
		}
		
		// Use 1-based indexing like C implementation
		topA := ps.A.GetValueAtPosition(1)
		chunkFirst := chunkValue(ps, chunk, 1)
		
		if chunk.Size < 2 {
			// Only one element left
			if topA == chunkFirst+1 {
				fmt.Printf("  Case 1: topA == chunkFirst+1, calling sortOne\n")
				sortOne(ps, chunk)
			} else {
				break
			}
		} else {
			// At least two elements
			chunkSecond := chunkValue(ps, chunk, 2)
			
			if topA == chunkFirst+1 && chunk.Size > 0 {
				fmt.Printf("  Case 1: topA == chunkFirst+1, calling sortOne\n")
				sortOne(ps, chunk)
			} else if topA == chunkSecond+1 && chunk.Size > 1 {
				fmt.Printf("  Case 2: topA == chunkSecond+1, calling easySortSecond\n")
				easySortSecond(ps, chunk)
			} else {
				fmt.Printf("  Case 3: no match, breaking\n")
				break
			}
		}
	}
	
	fmt.Printf("=== EASY_SORT END ===\n")
	fmt.Printf("Final chunk: loc=%v, size=%d\n", chunk.Loc, chunk.Size)
}

// easySortSecond handles the second element in easy sort (exactly like C implementation)
func easySortSecond(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("  easySortSecond: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	switch chunk.Loc {
	case stack.TOP_B:
		fmt.Printf("    Handling TOP_B\n")
		handleTopB(ps, chunk)
	case stack.BOTTOM_A:
		fmt.Printf("    Handling BOTTOM_A\n")
		handleBottomA(ps, chunk)
	case stack.BOTTOM_B:
		fmt.Printf("    Handling BOTTOM_B\n")
		handleBottomB(ps, chunk)
	}
	chunk.Size--
	fmt.Printf("    After easySortSecond: chunk size=%d\n", chunk.Size)
}

// handleTopB handles elements from TOP_B location (exactly like C implementation)
func handleTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("      handleTopB: before - A[0]=%d, B[0]=%d, B[1]=%d\n", 
		ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1), ps.B.GetValueAtPosition(2))
	
	stack.Swap_b(ps)
	stack.Push_a(ps)
	fmt.Printf("      Executed: Swap_b + Push_a\n")
	
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		fmt.Printf("      B[0] == A[0]-1, pushing another element\n")
		stack.Push_a(ps)
		chunk.Size--
	}
	
	fmt.Printf("      handleTopB: after - A[0]=%d, B[0]=%d\n", 
		ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
}

// handleBottomA handles elements from BOTTOM_A location (exactly like C implementation)
func handleBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("      handleBottomA: before - A[0]=%d, A[1]=%d\n", 
		ps.A.GetValueAtPosition(1), ps.A.GetValueAtPosition(2))
	
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	stack.Swap_a(ps)
	fmt.Printf("      Executed: R_rotate_a + R_rotate_a + Swap_a\n")
	
	if ps.A.GetValueAtPosition(1) == ps.A.GetValueAtPosition(2)-1 {
		fmt.Printf("      A[0] == A[1]-1, no additional rotate\n")
		chunk.Size--
	} else {
		fmt.Printf("      A[0] != A[1]-1, rotating A\n")
		stack.Rotate_a(ps)
	}
	
	fmt.Printf("      handleBottomA: after - A[0]=%d, A[1]=%d\n", 
		ps.A.GetValueAtPosition(1), ps.A.GetValueAtPosition(2))
}

// handleBottomB handles elements from BOTTOM_B location (exactly like C implementation)
func handleBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("      handleBottomB: before - A[0]=%d, B[0]=%d, B[1]=%d\n", 
		ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1), ps.B.GetValueAtPosition(2))
	
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	stack.Push_a(ps)
	fmt.Printf("      Executed: R_rotate_b + R_rotate_b + Push_a\n")
	
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		fmt.Printf("      B[0] == A[0]-1, pushing another element\n")
		stack.Push_a(ps)
		chunk.Size--
	} else {
		fmt.Printf("      B[0] != A[0]-1, rotating B\n")
		stack.Rotate_b(ps)
	}
	
	fmt.Printf("      handleBottomB: after - A[0]=%d, B[0]=%d\n", 
		ps.A.GetValueAtPosition(1), ps.B.GetValueAtPosition(1))
}
