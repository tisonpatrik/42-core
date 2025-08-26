package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// ChunkToTheTop moves the chunk to the top of its stack
func ChunkToTheTop(ps *ops.SortingState, to_sort *chunk.Chunk) {
	if to_sort.Loc == chunk.BOTTOM_B && stack.GettSize(ps.B) == to_sort.Size {
		to_sort.Loc = chunk.TOP_B
	}
	if to_sort.Loc == chunk.BOTTOM_A && stack.GettSize(ps.A) == to_sort.Size {
		to_sort.Loc = chunk.TOP_A
	}
}
