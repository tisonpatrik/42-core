package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(ps *ops.SortingState) {
	
	if stack.IsSorted(ps.A) {
		return
	}
	
	ChunkSort(ps)
}