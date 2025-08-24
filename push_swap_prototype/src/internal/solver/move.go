package solver

import (
	"push_swap_prototype/internal/stack"
)

// MoveFromTo moves an element from one location to another and returns 1 if successful
func MoveFromTo(ps *stack.PushSwapData, from, to stack.Loc) int {
	switch from {
	case stack.TOP_A:
		MoveFromTopA(ps, to)
	case stack.TOP_B:
		MoveFromTopB(ps, to)
	case stack.BOTTOM_A:
		MoveFromBottomA(ps, to)
	case stack.BOTTOM_B:
		MoveFromBottomB(ps, to)
	}
	return 1
}

// MoveFromTopA moves an element from TOP_A to the specified location
func MoveFromTopA(ps *stack.PushSwapData, to stack.Loc) {
	switch to {
	case stack.TOP_B:
		stack.Push_b(ps)
	case stack.BOTTOM_A:
		stack.Rotate_a(ps)
	case stack.BOTTOM_B:
		stack.Push_b(ps)
		stack.Rotate_b(ps)
	}
}

// MoveFromTopB moves an element from TOP_B to the specified location
func MoveFromTopB(ps *stack.PushSwapData, to stack.Loc) {
	switch to {
	case stack.TOP_A:
		stack.Push_a(ps)
	case stack.BOTTOM_B:
		stack.Rotate_b(ps)
	case stack.BOTTOM_A:
		stack.Push_a(ps)
		stack.Rotate_a(ps)
	}
}

// MoveFromBottomA moves an element from BOTTOM_A to the specified location
func MoveFromBottomA(ps *stack.PushSwapData, to stack.Loc) {
	switch to {
	case stack.TOP_A:
		stack.R_rotate_a(ps)
	case stack.TOP_B:
		stack.R_rotate_a(ps)
		stack.Push_b(ps)
	case stack.BOTTOM_B:
		stack.R_rotate_a(ps)
		stack.Push_b(ps)
		stack.Rotate_b(ps)
	}
}

// MoveFromBottomB moves an element from BOTTOM_B to the specified location
func MoveFromBottomB(ps *stack.PushSwapData, to stack.Loc) {

	switch to {
	case stack.TOP_B:
		stack.R_rotate_b(ps)
	case stack.TOP_A:
		stack.R_rotate_b(ps)
		stack.Push_a(ps)
	case stack.BOTTOM_A:
		stack.R_rotate_b(ps)
		stack.Push_a(ps)
		stack.Rotate_a(ps)
	}
}
