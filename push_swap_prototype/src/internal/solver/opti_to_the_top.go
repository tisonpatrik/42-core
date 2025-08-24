package solver

import (
	"push_swap_prototype/internal/stack"
)

// chunkToTheTop moves the chunk to the top of its stack
func chunkToTheTop(ps *stack.PushSwapData, chunk *stack.Chunk) {

	if chunk.Loc == stack.BOTTOM_B && ps.B.CurrentSize() == chunk.Size {
		chunk.Loc = stack.TOP_B
	}
	if chunk.Loc == stack.BOTTOM_A && ps.A.CurrentSize() == chunk.Size {
		chunk.Loc = stack.TOP_A
	}

}
