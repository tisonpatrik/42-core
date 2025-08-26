package ops

import (
	"push_swap_prototype/internal/stack"
)

func swap(stk *stack.Stack) {

	if (stack.GetValue(stk, stack.NextDown(stk, stk.Top)) == 0) {
		return
	}
	tmp := stack.GetValue(stk, stack.NextDown(stk, stk.Top))
	stack.Push(stk, stack.GetValue(stk, stk.Top))
	stack.Push(stk, tmp)
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
