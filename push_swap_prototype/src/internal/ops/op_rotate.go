package ops

import (
	"push_swap_prototype/internal/stack"
)

func rotate(stk *stack.Stack) {
	if stack.IsFull(stk) {
		stk.Bottom = stk.Top
		stk.Top = stack.NextDown(stk, stk.Top)
	} else {
		stk.Bottom = stack.NextDown(stk, stk.Bottom)
		stack.Push(stk, stack.GetValue(stk, stk.Top))
		stack.Push(stk, 0)
		stk.Top = stack.NextDown(stk, stk.Top)
	}
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