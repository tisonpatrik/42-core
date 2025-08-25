package solver

import (
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(numbers []int) () {
	
	ps := stack.NewPushSwapData()
	stack.FillStack(ps.A, numbers)
	if stack.IsSorted(ps) {
		return
	}
	
	ChunkSort(ps)
}