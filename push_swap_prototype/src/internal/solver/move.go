package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
)

// MoveFromTo moves an element from one location to another and returns 1 if successful
func MoveFromTo(ps *ops.SortingState, from, to chunk.Loc) int {

	// Perform the move operation
	switch from {
	case chunk.TOP_A:
		MoveFromTopA(ps, to)
	case chunk.TOP_B:
		MoveFromTopB(ps, to)
	case chunk.BOTTOM_A:
		MoveFromBottomA(ps, to)
	case chunk.BOTTOM_B:
		MoveFromBottomB(ps, to)
	}
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
