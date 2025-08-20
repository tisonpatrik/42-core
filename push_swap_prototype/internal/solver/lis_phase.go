package solver

import (
	"push_swap_prototype/internal/algo"
	"push_swap_prototype/internal/operations"
)

// ProcessLISPhase finds the LIS and sends non-LIS elements to stack B
// Returns the operations performed during this phase
func ProcessLISPhase(arr []int, stacks *operations.PushSwapStacks) []string {
	ops := make([]string, 0)
	
	// Initialize stack A with the input array
	stacks.InitializeFromSlice(arr)
	
	// Find LIS and send non-LIS to B
	keep := algo.FindLISIndices(arr)
	
	// Process elements by going through the array
	for i := range arr {
		if keep[i] {
			// Keep this element in A, rotate to next position
			stacks.RA()
			ops = append(ops, "ra")
		} else {
			// Send to stack B
			stacks.PB()
			ops = append(ops, "pb")
		}
	}
	
	return ops
}
