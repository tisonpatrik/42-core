package solver

import (
	"push_swap_prototype/internal/stack"
)

// moveFromTo moves an element from one location to another and returns 1 if successful
func moveFromTo(ps *stack.PushSwapData, from, to stack.Loc) int {
	switch from {
	case stack.TOP_A:
		moveFromTopA(ps, to)
	case stack.TOP_B:
		moveFromTopB(ps, to)
	case stack.BOTTOM_A:
		moveFromBottomA(ps, to)
	case stack.BOTTOM_B:
		moveFromBottomB(ps, to)
	}
	return 1
}

// moveFromTopA moves an element from TOP_A to the specified location
func moveFromTopA(ps *stack.PushSwapData, to stack.Loc) {
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

// moveFromTopB moves an element from TOP_B to the specified location
func moveFromTopB(ps *stack.PushSwapData, to stack.Loc) {
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

// moveFromBottomA moves an element from BOTTOM_A to the specified location
func moveFromBottomA(ps *stack.PushSwapData, to stack.Loc) {
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

// moveFromBottomB moves an element from BOTTOM_B to the specified location
func moveFromBottomB(ps *stack.PushSwapData, to stack.Loc) {
	
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
