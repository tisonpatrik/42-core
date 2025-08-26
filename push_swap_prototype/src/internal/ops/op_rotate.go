package ops

import (
	"push_swap_prototype/internal/stack"
)

func rotate(stk *stack.Stack) {
	if stack.GetSize(stk) <= 1 {
		return // Nothing to rotate
	}
	
	// Get the top value
	topValue := stack.GetValue(stk, 0)
	if topValue == stack.NullValue() {
		return
	}
	
	// Clear the top position
	oldTop := stack.GetTop(stk)
	stack.SetValueAt(stk, oldTop, stack.NullValue())
	
	// Update top pointer to next position
	stack.SetTop(stk, stack.Next(stk, oldTop))
	
	// Update bottom pointer to include the rotated element
	stack.SetBottom(stk, oldTop)
}

func RotateA(ps *SortingState) {
	rotate(ps.A)
	SaveOp(ps, RA)
}

func RotateB(ps *SortingState) {
	rotate(ps.B)
	SaveOp(ps, RB)
}

func RotateAB(ps *SortingState) {
	rotate(ps.A)
	rotate(ps.B)
	SaveOp(ps, RR)
}