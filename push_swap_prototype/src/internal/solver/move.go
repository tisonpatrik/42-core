package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// MoveFromTo moves an element from one location to another and returns 1 if successful
func MoveFromTo(ps *stack.SortingState, from, to stack.Loc) int {
	// Enhanced logging and validation
	stack.LogOperation(fmt.Sprintf("MoveFromTo(%d->%d)", from, to), ps)
	
	// Validate stack state before operation
	result := stack.ValidateStackState(ps, fmt.Sprintf("before MoveFromTo(%d->%d)", from, to))
	if !result.IsValid {
		stack.LogError("Stack validation failed before MoveFromTo:")
		for _, err := range result.Errors {
			stack.LogError("  - %s", err)
		}
		// Continue with operation but log the issue
	}
	
	// Log warnings if any
	for _, warning := range result.Warnings {
		stack.LogWarning("  - %s", warning)
	}
	
	// Perform the move operation
	switch from {
	case stack.TOP_A:
		stack.LogInfo("Moving from TOP_A")
		MoveFromTopA(ps, to)
	case stack.TOP_B:
		stack.LogInfo("Moving from TOP_B")
		MoveFromTopB(ps, to)
	case stack.BOTTOM_A:
		stack.LogInfo("Moving from BOTTOM_A")
		MoveFromBottomA(ps, to)
	case stack.BOTTOM_B:
		stack.LogInfo("Moving from BOTTOM_B")
		MoveFromBottomB(ps, to)
	}
	
	// Validate stack state after operation
	result = stack.ValidateStackState(ps, fmt.Sprintf("after MoveFromTo(%d->%d)", from, to))
	if !result.IsValid {
		stack.LogError("Stack validation failed after MoveFromTo:")
		for _, err := range result.Errors {
			stack.LogError("  - %s", err)
		}
	}
	
	// Log warnings if any
	for _, warning := range result.Warnings {
		stack.LogWarning("  - %s", warning)
	}
	
	stack.LogOperationResult(fmt.Sprintf("MoveFromTo(%d->%d)", from, to), ps)
	return 1
}

// MoveFromTopA moves an element from TOP_A to the specified location
func MoveFromTopA(ps *stack.SortingState, to stack.Loc) {
	
	switch to {
	case stack.TOP_B:
		stack.PushB(ps)
	case stack.BOTTOM_A:
		stack.RotateA(ps)
	case stack.BOTTOM_B:
		stack.PushB(ps)
		stack.RotateB(ps)
	}
	
}

// MoveFromTopB moves an element from TOP_B to the specified location
func MoveFromTopB(ps *stack.SortingState, to stack.Loc) {
	
	switch to {
	case stack.TOP_A:
		stack.PushA(ps)
	case stack.BOTTOM_B:
		stack.RotateB(ps)
	case stack.BOTTOM_A:
		stack.PushA(ps)
		stack.RotateA(ps)
	}
}

// MoveFromBottomA moves an element from BOTTOM_A to the specified location
func MoveFromBottomA(ps *stack.SortingState, to stack.Loc) {
	
	switch to {
	case stack.TOP_A:
		stack.ReverseRotateA(ps)
	case stack.TOP_B:
		stack.ReverseRotateA(ps)
		stack.PushB(ps)
	case stack.BOTTOM_B:
		stack.ReverseRotateA(ps)
		stack.PushB(ps)
		stack.RotateB(ps)
	}
	
}

// MoveFromBottomB moves an element from BOTTOM_B to the specified location
func MoveFromBottomB(ps *stack.SortingState, to stack.Loc) {

	switch to {
	case stack.TOP_A:
		stack.ReverseRotateB(ps)
		stack.PushA(ps)
	case stack.TOP_B:
		stack.ReverseRotateB(ps)
	case stack.BOTTOM_A:
		stack.ReverseRotateB(ps)
		stack.PushA(ps)
		stack.RotateA(ps)
	}
}
