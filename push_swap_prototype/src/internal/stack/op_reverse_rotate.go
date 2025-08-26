package stack

import "push_swap_prototype/internal/ops"

func reverseRotate(stk *Stack) {
	if IsFull(stk) {
		stk.Top = stk.Bottom
		stk.Bottom = NextUp(stk, stk.Bottom)
	} else {
		stk.Top = NextUp(stk, stk.Top)
		stk.Stack[stk.Top] = stk.Stack[stk.Bottom]
		stk.Stack[stk.Bottom] = 0
		stk.Bottom = NextUp(stk, stk.Bottom)
	}
}

func ReverseRotateA(ps *SortingState) {
	reverseRotate(ps.A)
	if ps.WritingMode {
		SaveOp(ps, ops.RRA)
	}
}

func ReverseRotateB(ps *SortingState) {
	reverseRotate(ps.B)
	if ps.WritingMode {
		SaveOp(ps, ops.RRB)
	}
}

func ReverseRotateAB(ps *SortingState) {
	reverseRotate(ps.A)
	reverseRotate(ps.B)
	if ps.WritingMode {
		SaveOp(ps, ops.RRR)
	}
}