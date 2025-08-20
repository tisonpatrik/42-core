package solver

import (
	"push_swap_prototype/internal/operations"
)

// SolvePushSwap solves the push swap problem using linked list stacks
// Returns the operations and final array
func SolvePushSwap(arr []int) ([]string, []int) {
	stacks := operations.NewPushSwapStacks()
	stacks.InitializeFromSlice(arr)
	
	// Phase 1: Find LIS and send non-LIS to B
	ops1 := ProcessLISPhase(arr, stacks)
	
	// Phase 2: Greedy return from B to A
	ops2 := ProcessGreedyPhase(stacks)
	
	// Phase 3: Final rotate - put minimum at top
	ops3 := ProcessFinalPhase(stacks)
	
	// Combine all operations
	allOps := make([]string, 0, len(ops1)+len(ops2)+len(ops3))
	allOps = append(allOps, ops1...)
	allOps = append(allOps, ops2...)
	allOps = append(allOps, ops3...)
	
	return allOps, stacks.GetStackASlice()
}
