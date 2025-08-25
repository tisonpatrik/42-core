package solver

import (
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(ps *stack.PushSwapData) {
	
	if stack.IsSorted(ps) {
		return
	}
	
	ChunkSort(ps)
}