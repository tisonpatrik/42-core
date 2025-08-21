package solver

import (
	"push_swap_prototype/internal/operations"
	"push_swap_prototype/internal/utils"
)

func SolvePushSwap(numbers []int) ([]operations.Operation, []int) {
	ps := operations.NewPushSwapData()
	operations.InitializeFromSlice(ps, numbers)

	if ps.A.Size() <= 1 || utils.IsSorted(ps.A.ToSlice()) {
		return []operations.Operation{}, ps.A.ToSlice()
	} else if ps.A.Size() == 3 {
		sort_three_a(ps)
	} else if ps.A.Size() == 5 {
		sort_five_a(ps)
	} else {
		chunk_sort(ps)
	}
	return ps.GetOperations(), ps.A.ToSlice()
}

func sort_three_a(ps *operations.PushSwapData) {
	// Use 1-based indexing like C implementation
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	third := ps.A.GetValueAtPosition(3)

	if first > second && third > second && third > first {
		operations.Swap_a(ps)
	} else if first > second && third > second && first > third {
		operations.Rotate_a(ps)
	} else if second > first && second > third && first > third {
		operations.R_rotate_a(ps)
	} else if second > first && second > third && third > first {
		operations.Swap_a(ps)
		operations.Rotate_a(ps)
	} else if first > second && second > third && first > third {
		operations.Swap_a(ps)
		operations.R_rotate_a(ps)
	}
}

func sort_five_a(ps *operations.PushSwapData) {
	for ps.A.Size() > 3 {
		if ps.A.PeekValue() == 1 || ps.A.PeekValue() == 2 {
			operations.Push_b(ps)
		} else {
			operations.Rotate_a(ps)
		}
	}
	
	if ps.B.Size() >= 2 {
		val1 := ps.B.GetValueAtPosition(0)
		val2 := ps.B.GetValueAtPosition(1)
		if val1 > val2 {
			operations.Swap_b(ps)
		}
	}
	
	sort_three_a(ps)
	
	for ps.B.Size() > 0 {
		operations.Push_a(ps)
	}
}