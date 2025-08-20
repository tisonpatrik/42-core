package solver

import (
	"push_swap_prototype/internal/operations"
)

// SolvePushSwap solves the push_swap puzzle using the simplest approach
func SolvePushSwap(numbers []int) ([]string, []int) {
	if len(numbers) <= 1 {
		return []string{}, numbers
	}

	// Initialize stacks
	stacks := operations.NewPushSwapStacks()
	stacks.InitializeFromSlice(numbers)
	
	operations := []string{}
	
	// The simplest approach:
	// 1. While stack A is not empty, find the minimum and push it to B
	for stacks.A.Size() > 0 {
		// Find the minimum element in stack A
		minValue := findMinInA(stacks)
		
		// Rotate stack A until the minimum is at the top
		for stacks.A.PeekValue() != minValue {
			stacks.RA()
			operations = append(operations, "ra")
		}
		
		// Push the minimum to stack B
		stacks.PB()
		operations = append(operations, "pb")
	}
	
	// 2. Push everything back from B to A (they're already in sorted order)
	for stacks.B.Size() > 0 {
		stacks.PA()
		operations = append(operations, "pa")
	}
	
	// Get final sorted result
	result := stacks.A.ToSlice()
	
	return operations, result
}

// findMinInA finds the minimum value in stack A
func findMinInA(stacks *operations.PushSwapStacks) int {
	if stacks.A.Size() == 0 {
		return 0
	}
	
	minValue := stacks.A.GetValueAtPosition(0)
	
	for i := 1; i < stacks.A.Size(); i++ {
		value := stacks.A.GetValueAtPosition(i)
		if value < minValue {
			minValue = value
		}
	}
	
	return minValue
}