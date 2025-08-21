package solver

import (
	"push_swap_prototype/internal/operations"
)

// easySort applies simple sorting optimizations
func easySort(ps *operations.PushSwapData, chunk *operations.Chunk) {
	for chunk.Loc != operations.TOP_A && chunk.Size > 0 {
		// Use 1-based indexing like C implementation
		if ps.A.GetValueAtPosition(1) == chunkValue(ps, chunk, 1)+1 && chunk.Size > 0 {
			sortOne(ps, chunk)
		} else if ps.A.GetValueAtPosition(1) == chunkValue(ps, chunk, 2)+1 && chunk.Size > 1 {
			easySortSecond(ps, chunk)
		} else {
			break
		}
	}
}

// easySortSecond handles the second element in easy sort
func easySortSecond(ps *operations.PushSwapData, chunk *operations.Chunk) {
	switch chunk.Loc {
	case operations.TOP_B:
		handleTopB(ps, chunk)
	case operations.BOTTOM_A:
		handleBottomA(ps, chunk)
	case operations.BOTTOM_B:
		handleBottomB(ps, chunk)
	}
	
	chunk.Size--
}

// handleTopB handles elements from TOP_B location
func handleTopB(ps *operations.PushSwapData, chunk *operations.Chunk) {
	operations.Swap_b(ps)
	operations.Push_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		operations.Push_a(ps)
		chunk.Size--
	}
}

// handleBottomA handles elements from BOTTOM_A location
func handleBottomA(ps *operations.PushSwapData, chunk *operations.Chunk) {
	operations.R_rotate_a(ps)
	operations.R_rotate_a(ps)
	operations.Swap_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) == ps.A.GetValueAtPosition(2)-1 {
		chunk.Size--
	} else {
		operations.Rotate_a(ps)
	}
}

// handleBottomB handles elements from BOTTOM_B location
func handleBottomB(ps *operations.PushSwapData, chunk *operations.Chunk) {
	operations.R_rotate_b(ps)
	operations.R_rotate_b(ps)
	operations.Push_a(ps)
	
	// Use 1-based indexing like C implementation
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		operations.Push_a(ps)
		chunk.Size--
	} else {
		operations.Rotate_b(ps)
	}
}
