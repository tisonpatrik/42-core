package solver

import (
	"push_swap_prototype/internal/operations"
)

// is_sorted checks if stack A is sorted by checking if each element equals its rank (1, 2, 3, ...)
// This is exactly like the C implementation: is_sorted(t_ps *data)
func is_sorted(ps *operations.PushSwapData) bool {
	if ps.A.Size() <= 1 {
		return true
	}
	
	// Check if each element equals its rank (1-based like C implementation)
	for i := 1; i <= ps.A.Size(); i++ {
		if ps.A.GetValueAtPosition(i) != i {
			return false
		}
	}
	return true
}

func SolvePushSwap(numbers []int) ([]operations.Operation, []int) {
	ps := operations.NewPushSwapData()
	operations.InitializeFromSlice(ps, numbers)

	if ps.A.Size() <= 1 || is_sorted(ps) {
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
		// Use 1-based indexing like C implementation: value(&data->b, 1) and value(&data->b, 2)
		val1 := ps.B.GetValueAtPosition(1)
		val2 := ps.B.GetValueAtPosition(2)
		// C code: if (value(&data->b, 1) < value(&data->b, 2)) swap_b(data)
		if val1 < val2 {
			operations.Swap_b(ps)
		}
	}
	
	sort_three_a(ps)
	
	for ps.B.Size() > 0 {
		operations.Push_a(ps)
	}
}