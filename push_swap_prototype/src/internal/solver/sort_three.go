package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// sortThree sorts a stack with 3 elements (equivalent to sort_three in C)
func SortThree(ps *ops.SortingState) {
	if stack.GetSize(ps.A) != 3 { return }

	a := stack.GetHead(ps.A)
	b := a.GetNext()
	c := b.GetNext()

	x, y, z := a.GetContent(), b.GetContent(), c.GetContent()

	// 5 případů (6 perms, 1 už seřazená)
	if x < y && y < z { return }             // sorted
	if x > y && y < z && x < z { ops.SwapA(ps); return }             // 213
	if x > y && y > z { ops.SwapA(ps); ops.ReverseRotateA(ps); return } // 321
	if x > y && y < z && x > z { ops.RotateA(ps); return }           // 231
	if x < y && y > z && x < z { ops.SwapA(ps); ops.RotateA(ps); return } // 132
	// x < y && y > z && x > z
	ops.ReverseRotateA(ps) // 312
}