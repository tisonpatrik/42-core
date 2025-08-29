package solver

import (
	"push_swap_prototype/internal/executor"
	"push_swap_prototype/internal/finalizer"
	"push_swap_prototype/internal/moves"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)


func SolvePushSwap(ps *ops.SortingState) {
	if stack.IsSorted(ps.A) {
		return
	}
	
	sort(ps)
}

func sort(ps *ops.SortingState) {
	ops.PushB(ps)
	ops.PushB(ps)

    for stack.GetSize(ps.A) > 3 {
        pos := moves.CheapestAtoB(ps) // už nese CostA/CostB podepsané
        executor.ApplyCombined(ps, pos, true) // true = push do B
    }

	SortThree(ps)
	finalizer.FinalizeSorting(ps)
}

