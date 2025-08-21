package solver

import (
	"push_swap_prototype/internal/operations"
)

// splitMaxReduction reduces the max chunk size when elements are moved (exactly like C implementation)
func splitMaxReduction(ps *operations.PushSwapData, max *operations.Chunk) {
	a := ps.A
	
	// Use 1-based indexing like C implementation
	if max.Loc == operations.TOP_A && max.Size == 3 && isConsecutive(
		a.GetValueAtPosition(1), a.GetValueAtPosition(2), 
		a.GetValueAtPosition(3), a.GetValueAtPosition(4)) && 
		aPartlySort(ps, 4) {
		sortThree(ps, max)
		return
	}
	
	if max.Loc == operations.TOP_A && a.GetValueAtPosition(1) == a.GetValueAtPosition(3)-1 && 
		aPartlySort(ps, 3) {
		operations.Swap_a(ps)
		max.Size--
	}
	
	if max.Loc == operations.TOP_A && aPartlySort(ps, 1) {
		max.Size--
	}
}

// aPartlySort checks if stack A is partially sorted from a given position (exactly like C implementation)
func aPartlySort(ps *operations.PushSwapData, from int) bool {
	a := ps.A
	
	// Start from the top position like C implementation
	i := a.GetTop()
	
	// Move down 'from' positions like C: while (--from) i = next_down(a, i);
	for from > 1 {
		i = a.NextDown(i)
		from--
	}
	
	// Check if values are consecutive going down like C implementation
	for a.Value(i) != a.Size() {
		value := a.Value(i)
		i = a.NextDown(i)
		if a.Value(i) != value+1 {
			return false
		}
	}
	return true
}

// isConsecutive checks if four numbers are consecutive (exactly like C implementation)
func isConsecutive(a, b, c, d int) bool {
	// Sort only the first three numbers, like C implementation
	sortThreeNumbers(&a, &b, &c)
	return (b-a == 1) && (c-b == 1) && (d-c == 1)
}

// sortThreeNumbers sorts three numbers in ascending order (exactly like C implementation)
func sortThreeNumbers(a, b, c *int) {
	if *a > *b {
		temp := *a
		*a = *b
		*b = temp
	}
	if *a > *c {
		temp := *a
		*a = *c
		*c = temp
	}
	if *b > *c {
		temp := *b
		*b = *c
		*c = temp
	}
}
