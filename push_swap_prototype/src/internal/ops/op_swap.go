package ops

import (
	"push_swap_prototype/internal/stack"
)

func swap(stk *stack.Stack) {

	if (stack.GetValue(stk, stack.Next(stk, stack.GetTop(stk))) == 0) {
		return
	}
	tmp := stack.GetValue(stk, stack.Next(stk, stack.GetTop(stk)))
	stack.Push(stk, stack.GetValue(stk, stack.GetTop(stk)))
	stack.Push(stk, tmp)
}


func SwapA(ps *SortingState) {
	swap(ps.A)
	SaveOp(ps, SA)
}
func SwapB(ps *SortingState) {
	swap(ps.B)
	SaveOp(ps, SB)
}
func SwapAB(ps *SortingState) {
	swap(ps.A)
	swap(ps.B)
	SaveOp(ps, SS)
}
