package solver

import (
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(ps *stack.SortingState) {
	
	if stack.IsSorted(ps.A) {
		return
	}
	
	ChunkSort(ps)
}