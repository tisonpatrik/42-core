package ops

import "push_swap_prototype/internal/stack"

func swap(stk *stack.Stack) bool {
	return stack.Swap(stk)
}



func SwapA(ps *SortingState) {
	if swap(ps.A) {
		SaveOp(ps, SA)
	}
}

func SwapB(ps *SortingState) {
	if swap(ps.B) {
		SaveOp(ps, SB)
	}
}

func SwapAB(ps *SortingState) {
	a := swap(ps.A)
	b := swap(ps.B)
	if a && b {
		SaveOp(ps, SS)
	}
}
