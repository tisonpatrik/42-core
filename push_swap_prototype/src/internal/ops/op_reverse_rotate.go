package ops

import (
	"push_swap_prototype/internal/stack"
)

func reverseRotate(stk *stack.Stack) {
	if stack.IsFull(stk) {
		stk.Top = stk.Bottom
		stk.Bottom = stack.NextUp(stk, stk.Bottom)
	} else {
		stk.Top = stack.NextUp(stk, stk.Top)
		stack.Push(stk, stack.GetValue(stk, stk.Bottom))
		stack.Push(stk, 0)
		stk.Bottom = stack.NextUp(stk, stk.Bottom)
	}
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