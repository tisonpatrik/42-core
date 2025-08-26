package ops

import (
	"push_swap_prototype/internal/stack"
)

func reverseRotate(stk *stack.Stack) {
	if stack.GettSize(stk) <= 1 {
		return // Nothing to rotate
	}
	
	// Get the bottom value
	bottomValue := stack.GetValue(stk, stack.GettSize(stk)-1)
	if bottomValue == stack.NullValue() {
		return
	}
	
	// Clear the bottom position
	oldBottom := stack.GetBottom(stk)
	stack.SetValueAt(stk, oldBottom, stack.NullValue())
	
	// Update bottom pointer to previous position
	stack.SetBottom(stk, stack.Previous(stk, oldBottom))
	
	// Update top pointer to include the rotated element
	stack.SetTop(stk, oldBottom)
}

func ReverseRotateA(ps *	SortingState) {
	reverseRotate(ps.A)
	if ps.WritingMode {
		SaveOp(ps, RRA)
	}
}

func ReverseRotateB(ps *SortingState) {
	reverseRotate(ps.B)
	if ps.WritingMode {
		SaveOp(ps, RRB)
	}
}

func ReverseRotateAB(ps *SortingState) {
	reverseRotate(ps.A)
	reverseRotate(ps.B)
	if ps.WritingMode {
		SaveOp(ps, RRR)
	}
}