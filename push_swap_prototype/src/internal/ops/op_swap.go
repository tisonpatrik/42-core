package ops

import (
	"push_swap_prototype/internal/stack"
)

func swap(stk *stack.Stack) {

	if (stk.Stack[stack.NextDown(stk, stk.Top)] == 0) {
		return
	}
	tmp := stk.Stack[stack.NextDown(stk, stk.Top)]
	stk.Stack[stack.NextDown(stk, stk.Top)] = stk.Stack[stk.Top]
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
