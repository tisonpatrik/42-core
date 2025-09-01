package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// SortThree sorts a stack with exactly 3 elements using the optimal sequence of operations.
// It handles all 6 possible permutations of 3 elements with minimal operations.
func SortThree(ps *ops.SortingState) {
	if stack.GetSize(ps.A) != 3 { return }

	a := stack.GetHead(ps.A)
	b := a.GetNext()
	c := b.GetNext()

	x, y, z := a.GetContent(), b.GetContent(), c.GetContent()

	// 5 cases (6 perms, 1 already sorted)
	if x < y && y < z { return }             // sorted
	if x > y && y < z && x < z { ops.SwapA(ps); return }             // 213
	if x > y && y > z { ops.SwapA(ps); ops.ReverseRotateA(ps); return } // 321
	if x > y && y < z && x > z { ops.RotateA(ps); return }           // 231
	if x < y && y > z && x < z { ops.SwapA(ps); ops.RotateA(ps); return } // 132
	// x < y && y > z && x > z
	ops.ReverseRotateA(ps) // 312
}