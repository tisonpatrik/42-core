package solver

import (
	"push_swap_prototype/internal/stack"
)

func SolvePushSwap(numbers []int) ([]stack.Operation, []int) {
	
	ps := stack.NewPushSwapDataWithCapacity(len(numbers))
	stack.InitializeFromSlice(ps, numbers)

	if stack.IsSorted(ps) {
		return []stack.Operation{}, ps.A.ToSlice()
	}
	
	ChunkSort(ps)
	return ps.GetOperations(), ps.A.ToSlice()
}