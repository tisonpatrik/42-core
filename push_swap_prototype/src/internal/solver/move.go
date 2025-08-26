package solver

import (
	"fmt"
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
)

// MoveFromTo moves an element from one location to another and returns 1 if successful
func MoveFromTo(ps *ops.SortingState, from, to chunk.Loc) int {
	// Enhanced logging and validation
	ops.LogOperation(fmt.Sprintf("MoveFromTo(%d->%d)", from, to), ps)
	
	// Validate stack state before operation
	result := ops.ValidateStackState(ps, fmt.Sprintf("before MoveFromTo(%d->%d)", from, to))
	if !result.IsValid {
		ops.LogError("Stack validation failed before MoveFromTo:")
		for _, err := range result.Errors {
			ops.LogError("  - %s", err)
		}
		// Continue with operation but log the issue
	}
	
	// Log warnings if any
	for _, warning := range result.Warnings {
		ops.LogWarning("  - %s", warning)
	}
	
	// Perform the move operation
	switch from {
	case chunk.TOP_A:
		ops.LogInfo("Moving from TOP_A")
		MoveFromTopA(ps, to)
	case chunk.TOP_B:
		ops.LogInfo("Moving from TOP_B")
		MoveFromTopB(ps, to)
	case chunk.BOTTOM_A:
		ops.LogInfo("Moving from BOTTOM_A")
		MoveFromBottomA(ps, to)
	case chunk.BOTTOM_B:
		ops.LogInfo("Moving from BOTTOM_B")
		MoveFromBottomB(ps, to)
	}
	
	// Validate stack state after operation
	result = ops.ValidateStackState(ps, fmt.Sprintf("after MoveFromTo(%d->%d)", from, to))
	if !result.IsValid {
		ops.LogError("Stack validation failed after MoveFromTo:")
		for _, err := range result.Errors {
			ops.LogError("  - %s", err)
		}
	}
	
	// Log warnings if any
	for _, warning := range result.Warnings {
		ops.LogWarning("  - %s", warning)
	}
	
	ops.LogOperationResult(fmt.Sprintf("MoveFromTo(%d->%d)", from, to), ps)
	return 1
}

// MoveFromTopA moves an element from TOP_A to the specified location
func MoveFromTopA(ps *ops.SortingState, to chunk.Loc) {
	
	switch to {
	case chunk.TOP_B:
		ops.PushB(ps)
	case chunk.BOTTOM_A:
		ops.RotateA(ps)
	case chunk.BOTTOM_B:
		ops.PushB(ps)
		ops.RotateB(ps)
	}
	
}

// MoveFromTopB moves an element from TOP_B to the specified location
func MoveFromTopB(ps *ops.SortingState, to chunk.Loc) {
	
	switch to {
	case chunk.TOP_A:
		ops.PushA(ps)
	case chunk.BOTTOM_B:
		ops.RotateB(ps)
	case chunk.BOTTOM_A:
		ops.PushA(ps)
		ops.RotateA(ps)
	}
}

// MoveFromBottomA moves an element from BOTTOM_A to the specified location
func MoveFromBottomA(ps *ops.SortingState, to chunk.Loc) {
	
	switch to {
	case chunk.TOP_A:
		ops.ReverseRotateA(ps)
	case chunk.TOP_B:
		ops.ReverseRotateA(ps)
		ops.PushB(ps)
	case chunk.BOTTOM_B:
		ops.ReverseRotateA(ps)
		ops.PushB(ps)
		ops.RotateB(ps)
	}
	
}

// MoveFromBottomB moves an element from BOTTOM_B to the specified location
func MoveFromBottomB(ps *ops.SortingState, to chunk.Loc) {

	switch to {
	case chunk.TOP_A:
		ops.ReverseRotateB(ps)
		ops.PushA(ps)
	case chunk.TOP_B:
		ops.ReverseRotateB(ps)
	case chunk.BOTTOM_A:
		ops.ReverseRotateB(ps)
		ops.PushA(ps)
		ops.RotateA(ps)
	}
}
