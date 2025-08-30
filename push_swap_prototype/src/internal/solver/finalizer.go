package solver

import (
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)




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
	cost := moves.SignedCost(minIdx, sizeA)
	for cost > 0 { ops.RotateA(ps); cost-- }
	for cost < 0 { ops.ReverseRotateA(ps); cost++ }
}
