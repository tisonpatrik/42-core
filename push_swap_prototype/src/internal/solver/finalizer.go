package solver

import (
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)



func AlignMinToTop(ps *ops.SortingState) {
	sizeA := stack.GetSize(ps.A)
	if sizeA == 0 {
		return
	}

	// Najdi index minima v A (0 = top)
	minIdx := 0
	minVal := stack.GetHead(ps.A).GetContent()
	i := 0
	for n := stack.GetHead(ps.A); n != nil; n, i = n.GetNext(), i+1 {
		if n.GetContent() < minVal {
			minVal = n.GetContent()
			minIdx = i
		}
	}

	// Podepsaný náklad a prosté dotočení A
	cost := moves.SignedCost(minIdx, sizeA)
	for cost > 0 {
		ops.RotateA(ps)   // ra
		cost--
	}
	for cost < 0 {
		ops.ReverseRotateA(ps) // rra
		cost++
	}
}
