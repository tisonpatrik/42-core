package stack

// swap swaps the first 2 elements at the top of a stack (exactly like C swap)
func swap(stk *Stack) {

	if (stk.Stack[NextDown(stk, stk.Top)] == 0) {
		return
	}
	tmp := stk.Stack[NextDown(stk, stk.Top)]
	stk.Stack[NextDown(stk, stk.Top)] = stk.Stack[stk.Top]
	stk.Stack[stk.Top] = tmp
}


func SwapA(ps *SortingState) {
	swap(ps.A)
	if ps.WritingMode {
		SaveOp(ps, SA)
	}
}
func SwapB(ps *SortingState) {
	swap(ps.B)
	if ps.WritingMode {
		SaveOp(ps, SB)
	}
}
func SwapAB(ps *SortingState) {
	swap(ps.A)
	swap(ps.B)
	if ps.WritingMode {
		SaveOp(ps, SS)
	}
}
