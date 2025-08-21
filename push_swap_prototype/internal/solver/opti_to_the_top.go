package solver

import (
	"push_swap_prototype/internal/operations"
)

// chunkToTheTop moves the chunk to the top of its stack
func chunkToTheTop(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// Exactly like C implementation - just update location, don't move elements
	if chunk.Loc == operations.BOTTOM_B && ps.B.CurrentSize() == chunk.Size {
		chunk.Loc = operations.TOP_B
	}
	if chunk.Loc == operations.BOTTOM_A && ps.A.CurrentSize() == chunk.Size {
		chunk.Loc = operations.TOP_A
	}
}
