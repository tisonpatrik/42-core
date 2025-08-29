package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// sortThree sorts a stack with 3 elements (equivalent to sort_three in C)
func SortThree(ps *ops.SortingState) {
	if stack.IsEmpty(ps.A) || stack.GetSize(ps.A) < 3 {
		return
	}
	
	// Get the first three nodes
	first := stack.GetHead(ps.A)
	second := first.GetNext()
	third := second.GetNext()
	
	a := first.GetContent()
	b := second.GetContent()
	c := third.GetContent()
	
	switch {
	case a < b && b < c: // 1,2,3 - already sorted
		return
	case a < b && b > c && a < c: // 1,3,2
		ops.SwapA(ps)
		ops.RotateA(ps)
	case a > b && b < c && a < c: // 2,1,3
		ops.SwapA(ps)
	case a < b && b > c && a > c: // 2,3,1
		ops.ReverseRotateA(ps)
	case a > b && b < c && a > c: // 3,1,2
		ops.RotateA(ps)
	case a > b && b > c: // 3,2,1
		ops.SwapA(ps)
		ops.ReverseRotateA(ps)
	}
}