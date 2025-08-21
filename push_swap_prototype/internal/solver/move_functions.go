package solver

import (
	"push_swap_prototype/internal/operations"
)

// moveFromTo moves an element from one location to another and returns 1 if successful
func moveFromTo(ps *operations.PushSwapData, from, to operations.Loc) int {
	switch from {
	case operations.TOP_A:
		moveFromTopA(ps, to)
	case operations.TOP_B:
		moveFromTopB(ps, to)
	case operations.BOTTOM_A:
		moveFromBottomA(ps, to)
	case operations.BOTTOM_B:
		moveFromBottomB(ps, to)
	}
	return 1
}

// moveFromTopA moves an element from TOP_A to the specified location
func moveFromTopA(ps *operations.PushSwapData, to operations.Loc) {
	switch to {
	case operations.TOP_B:
		operations.Push_b(ps)
	case operations.BOTTOM_A:
		operations.Rotate_a(ps)
	case operations.BOTTOM_B:
		operations.Push_b(ps)
		operations.R_rotate_b(ps)
	}
}

// moveFromTopB moves an element from TOP_B to the specified location
func moveFromTopB(ps *operations.PushSwapData, to operations.Loc) {
	switch to {
	case operations.TOP_A:
		operations.Push_a(ps)
	case operations.BOTTOM_B:
		operations.R_rotate_b(ps)
	case operations.BOTTOM_A:
		operations.Push_a(ps)
		operations.Rotate_a(ps)
	}
}

// moveFromBottomA moves an element from BOTTOM_A to the specified location
func moveFromBottomA(ps *operations.PushSwapData, to operations.Loc) {
	switch to {
	case operations.TOP_A:
		operations.R_rotate_a(ps)
	case operations.TOP_B:
		operations.R_rotate_a(ps)
		operations.Push_b(ps)
	case operations.BOTTOM_B:
		operations.R_rotate_a(ps)
		operations.Push_b(ps)
		operations.R_rotate_b(ps)
	}
}

// moveFromBottomB moves an element from BOTTOM_B to the specified location
func moveFromBottomB(ps *operations.PushSwapData, to operations.Loc) {
	switch to {
	case operations.TOP_B:
		operations.R_rotate_b(ps)
	case operations.TOP_A:
		operations.R_rotate_b(ps)
		operations.Push_a(ps)
	case operations.BOTTOM_A:
		operations.R_rotate_b(ps)
		operations.Push_a(ps)
		operations.Rotate_a(ps)
	}
}
