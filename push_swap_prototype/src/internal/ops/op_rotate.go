package ops

import "push_swap_prototype/internal/stack"

func rotate(stk *stack.Stack) bool {
    return stack.Rotate(stk)
}

// Shift up all elements of stack a by 1.
// The first element becomes the last one.
func RotateA(ps *SortingState) {
    if rotate(ps.A) {
        SaveOp(ps, RA)
    }
}

// Shift up all elements of stack b by 1.
func RotateB(ps *SortingState) {
    if rotate(ps.B) {
        SaveOp(ps, RB)
    }
}

func RotateAB(ps *SortingState) {
    rotatedA := rotate(ps.A)
    rotatedB := rotate(ps.B)
    if rotatedA && rotatedB {
        SaveOp(ps, RR)
    } else if rotatedA {
        SaveOp(ps, RA)
    } else if rotatedB {
        SaveOp(ps, RB)
    }
}