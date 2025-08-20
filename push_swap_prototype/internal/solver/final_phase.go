package solver

import "push_swap_prototype/internal/operations"

// ProcessFinalPhase rotates the stack to put the minimum element at the top
// Returns the operations performed during this phase
func ProcessFinalPhase(stacks *operations.PushSwapStacks) []string {
	ops := make([]string, 0)
	
	// Final rotate - put minimum at top
	finalSlice := stacks.GetStackASlice()
	minPos := findMinPosition(finalSlice)
	
	if minPos <= len(finalSlice)/2 {
		// Rotate up is more efficient
		for i := 0; i < minPos; i++ {
			stacks.RA()
			ops = append(ops, "ra")
		}
	} else {
		// Rotate down is more efficient
		for i := 0; i < len(finalSlice)-minPos; i++ {
			stacks.RRA()
			ops = append(ops, "rra")
		}
	}
	
	return ops
}
