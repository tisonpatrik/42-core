package stack

import "push_swap_prototype/internal/ops"

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
		SaveOp(ps, ops.SA)
	}
}
func SwapB(ps *SortingState) {
	swap(ps.B)
	if ps.WritingMode {
		SaveOp(ps, ops.SB)
	}
}
func SwapAB(ps *SortingState) {
	swap(ps.A)
	swap(ps.B)
	if ps.WritingMode {
		SaveOp(ps, ops.SS)
	}
}
