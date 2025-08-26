package ops

import (
	"push_swap_prototype/internal/stack"
)

func rotate(stk *stack.Stack) {
	if stack.GettSize(stk) <= 1 {
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
	if ps.WritingMode {
		SaveOp(ps, RA)
	}
}

func RotateB(ps *SortingState) {
	rotate(ps.B)
	if ps.WritingMode {
		SaveOp(ps, RB)
	}
}

func RotateAB(ps *SortingState) {
	rotate(ps.A)
	rotate(ps.B)
	if ps.WritingMode {
		SaveOp(ps, RR)
	}
}