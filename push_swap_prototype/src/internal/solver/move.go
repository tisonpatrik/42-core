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
		stack.PushB(ps)
	case stack.BOTTOM_A:
		stack.RotateA(ps)
	case stack.BOTTOM_B:
		stack.PushB(ps)
		stack.RotateB(ps)
	}
	
}

// MoveFromTopB moves an element from TOP_B to the specified location
func MoveFromTopB(ps *stack.PushSwapData, to stack.Loc) {
	
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
func MoveFromBottomA(ps *stack.PushSwapData, to stack.Loc) {
	
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
func MoveFromBottomB(ps *stack.PushSwapData, to stack.Loc) {

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
