package solver

import (
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(numbers []int) (*stack.PushSwapData) {
	
	ps := stack.NewPushSwapData()
	stack.FillStack(ps.A, numbers)
	if stack.IsSorted(ps) {
		return ps
	}
	
	ChunkSort(ps)
	return ps
}