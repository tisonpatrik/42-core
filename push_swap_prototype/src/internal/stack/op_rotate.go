package stack

func rotate(stk *Stack) {
	if IsFull(stk) {
		stk.Bottom = stk.Top
		stk.Top = NextDown(stk, stk.Top)
	} else {
		stk.Bottom = NextDown(stk, stk.Bottom)
		stk.Stack[stk.Bottom] = stk.Stack[stk.Top]
		stk.Stack[stk.Top] = 0
		stk.Top = NextDown(stk, stk.Top)
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