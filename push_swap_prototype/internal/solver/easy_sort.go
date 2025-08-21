package solver

import "push_swap_prototype/internal/stack"

// easySort applies simple sorting optimizations (exactly like C implementation)
func easySort(ps *stack.PushSwapData, chunk *stack.Chunk) {
	// Exactly like C: while (to_sort->loc != TOP_A && to_sort->size)
	for chunk.Loc != stack.TOP_A && chunk.Size != 0 {
		// Use 1-based indexing like C implementation
		topA := ps.A.GetValueAtPosition(1)
		chunkFirst := chunkValue(ps, chunk, 1)
		chunkSecond := chunkValue(ps, chunk, 2)
		
		if topA == chunkFirst+1 && chunk.Size > 0 {
			sortOne(ps, chunk)
		} else if topA == chunkSecond+1 && chunk.Size > 1 {
			easySortSecond(ps, chunk)
		} else {
			break
		}
	}
}

// easySortSecond handles the second element in easy sort (exactly like C implementation)
func easySortSecond(ps *stack.PushSwapData, chunk *stack.Chunk) {
	switch chunk.Loc {
	case stack.TOP_B:
		handleTopB(ps, chunk)
	case stack.BOTTOM_A:
		handleBottomA(ps, chunk)
	case stack.BOTTOM_B:
		handleBottomB(ps, chunk)
	}
	chunk.Size--
}

// handleTopB handles elements from TOP_B location (exactly like C implementation)
func handleTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.Swap_b(ps)
	stack.Push_a(ps)
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
		chunk.Size--
	}
}

// handleBottomA handles elements from BOTTOM_A location (exactly like C implementation)
func handleBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	stack.Swap_a(ps)
	if ps.A.GetValueAtPosition(1) == ps.A.GetValueAtPosition(2)-1 {
		chunk.Size--
	} else {
		stack.Rotate_a(ps)
	}
}

// handleBottomB handles elements from BOTTOM_B location (exactly like C implementation)
func handleBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	stack.Push_a(ps)
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
		chunk.Size--
	} else {
		stack.Rotate_b(ps)
	}
}
