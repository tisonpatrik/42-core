package solver

import (
	"push_swap_prototype/internal/stack"
)

// ChunkToTheTop moves the chunk to the top of its stack
func ChunkToTheTop(ps *stack.PushSwapData, chunk *stack.Chunk) {
	if chunk.Loc == stack.BOTTOM_B && stack.CurrentSize(ps.B) == chunk.Size {
		chunk.Loc = stack.TOP_B
	}
	if chunk.Loc == stack.BOTTOM_A && stack.CurrentSize(ps.A) == chunk.Size {
		chunk.Loc = stack.TOP_A
	}
}
