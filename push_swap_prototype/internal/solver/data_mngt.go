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
