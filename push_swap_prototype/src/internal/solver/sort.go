package solver

import (
	"push_swap_prototype/internal/stack"
)


func SolvePushSwap(numbers []int) ([]stack.Operation, []int) {
	ps := stack.NewPushSwapData()
	stack.InitializeFromSlice(ps, numbers)

	if ps.A.Size() <= 1 || stack.IsSorted(ps) {
		return []stack.Operation{}, ps.A.ToSlice()
	} else if ps.A.Size() == 3 {
		sort_three_a(ps)
	} else if ps.A.Size() == 5 {
		sort_five_a(ps)
	} else {
		chunk_sort(ps)
	}
	return ps.GetOperations(), ps.A.ToSlice()
}

func sort_three_a(ps *stack.PushSwapData) {
	// Use 1-based indexing like C implementation
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	third := ps.A.GetValueAtPosition(3)

	if first > second && third > second && third > first {
		stack.Swap_a(ps)
	} else if first > second && third > second && first > third {
		stack.Rotate_a(ps)
	} else if second > first && second > third && first > third {
		stack.R_rotate_a(ps)
	} else if second > first && second > third && third > first {
		stack.Swap_a(ps)
		stack.Rotate_a(ps)
	} else if first > second && second > third && first > third {
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	}
}

func sort_five_a(ps *stack.PushSwapData) {
	for ps.A.Size() > 3 {
		if ps.A.PeekValue() == 1 || ps.A.PeekValue() == 2 {
			stack.Push_b(ps)
		} else {
			stack.Rotate_a(ps)
		}
	}
	
	if ps.B.GetValueAtPosition(1) < ps.B.GetValueAtPosition(2) {
		stack.Swap_b(ps)
	}
	
	sort_three_a(ps)
	stack.Push_a(ps)
	stack.Push_a(ps)
}

