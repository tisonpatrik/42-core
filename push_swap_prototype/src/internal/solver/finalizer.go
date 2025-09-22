package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/selector"
	"push_swap_prototype/internal/stack"
)

// AlignMinToTop rotates stack A to bring the minimum element to the top via the shortest path.
// This is the final step in the push_swap algorithm to ensure proper ordering.
func AlignMinToTop(ps *ops.SortingState) {
	sizeA := stack.GetSize(ps.A)
	if sizeA == 0 { return }

	minIdx := 0
	minVal := stack.GetHead(ps.A).GetContent()
	for i, n := 0, stack.GetHead(ps.A); n != nil; n, i = n.GetNext(), i+1 {
		if v := n.GetContent(); v < minVal {
			minVal, minIdx = v, i
		}
	}
	cost := selector.SignedCost(minIdx, sizeA)
	for cost > 0 { ops.RotateA(ps); cost-- }
	for cost < 0 { ops.ReverseRotateA(ps); cost++ }
}
