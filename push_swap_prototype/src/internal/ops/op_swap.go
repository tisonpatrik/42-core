package ops

import "push_swap_prototype/internal/stack"

func swap(stk *stack.Stack) bool {
	return stack.Swap(stk)
}

// sa (swap a): Swap the first 2 elements at the top of stack a.
// Do nothing if there is only one element or none.

func SwapA(ps *SortingState) {
	if swap(ps.A) {
		SaveOp(ps, SA)
	}
}
// sb (swap b): Swap the first 2 elements at the top of stack b.
// Do nothing if there is only one element or none.
func SwapB(ps *SortingState) {
	if swap(ps.B) {
		SaveOp(ps, SB)
	}
}

// ss : sa and sb at the same time.
func SwapAB(ps *SortingState) {
	a := swap(ps.A)
	b := swap(ps.B)
	switch {
	case a && b:
		SaveOp(ps, SS)
	case a:
		SaveOp(ps, SA)
	case b:
		SaveOp(ps, SB)
	}
}
