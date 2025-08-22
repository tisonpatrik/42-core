package stack

// is_sorted checks if stack A is sorted in ascending order
// This is exactly like the C implementation: is_sorted(t_ps *data)
func IsSorted(ps *PushSwapData) bool {
	if ps.A.Size() <= 1 {
		return true
	}
	
	// Check if each element is less than or equal to the next element
	// This works for any numbers, including [0,1,2,3...] or [1,2,3,4...]
	for i := 1; i < ps.A.Size(); i++ {
		if ps.A.GetValueAtPosition(i) > ps.A.GetValueAtPosition(i+1) {
			return false
		}
	}
	return true
}
