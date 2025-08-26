package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// ChunkToTheTop moves the chunk to the top of its stack
func ChunkToTheTop(ps *ops.SortingState, to_sort *chunk.Chunk) {
	if chunk.GetLoc(to_sort) == chunk.BOTTOM_B && stack.GetSize(ps.B) == chunk.GetSize(to_sort) {
		chunk.SetLoc(to_sort, chunk.TOP_B)
	}
	if chunk.GetLoc(to_sort) == chunk.BOTTOM_A && stack.GetSize(ps.A) == chunk.GetSize(to_sort) {
		chunk.SetLoc(to_sort, chunk.TOP_A)
	}
}
