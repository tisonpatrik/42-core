package solver

import (
	"push_swap_prototype/internal/ops"
	optimizer "push_swap_prototype/internal/peephole"
	"push_swap_prototype/internal/selector"
	"push_swap_prototype/internal/separator"
	"push_swap_prototype/internal/stack"
)


func SolvePushSwap(ps *ops.SortingState) {
	if stack.IsSorted(ps.A) { return }

	separator.PushNonLISIntoB(ps, true)



	candK := 30

	for stack.GetSize(ps.A) > 3 {
		pos := selector.PickNearBest(ps, candK)
		ApplyCombined(ps, pos, true)
	}

	SortThree(ps)

	for !stack.IsEmpty(ps.B) {
		pos := selector.PickNearBest(ps, candK)
		ApplyCombined(ps, pos, false) // pa
	}

	AlignMinToTop(ps)

	optimizer.OptimizeOps(ps.OpList)
}


