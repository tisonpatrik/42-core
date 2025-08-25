package solver

import (
	"push_swap_prototype/internal/stack"
)

// ChunkToTheTop moves the chunk to the top of its stack
func ChunkToTheTop(ps *stack.PushSwapData, to_sort *stack.Chunk) {
	if to_sort.Loc == stack.BOTTOM_B && stack.CurrentSize(ps.B) == to_sort.Size {
		to_sort.Loc = stack.TOP_B
	}
	if to_sort.Loc == stack.BOTTOM_A && stack.CurrentSize(ps.A) == to_sort.Size {
		to_sort.Loc = stack.TOP_A
	}
}
