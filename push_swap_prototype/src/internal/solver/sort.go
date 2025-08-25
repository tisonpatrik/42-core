package solver

import (
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(numbers []int) (*stack.PushSwapData) {
	
	ps := stack.NewPushSwapData()
	
	// Initialize both stacks with the correct size (like C init_stack)
	stack.InitStacks(ps, len(numbers))
	
	// Fill only stack A with values (like C fill_stack)
	stack.FillStack(ps.A, numbers)
	
	if stack.IsSorted(ps) {
		return ps
	}
	
	ChunkSort(ps)
	return ps
}