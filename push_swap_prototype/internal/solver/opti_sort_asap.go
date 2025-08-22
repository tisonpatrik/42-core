package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// splitMaxReduction reduces the max chunk size when elements are moved (exactly like C implementation)
func splitMaxReduction(ps *stack.PushSwapData, max *stack.Chunk) {
	fmt.Printf("      splitMaxReduction: max chunk loc=%v, size=%d\n", max.Loc, max.Size)
	
	a := ps.A
	
	// Use 1-based indexing like C implementation
	if max.Loc == stack.TOP_A && max.Size == 3 && isConsecutive(
		a.GetValueAtPosition(1), a.GetValueAtPosition(2), 
		a.GetValueAtPosition(3), a.GetValueAtPosition(4)) && 
		aPartlySort(ps, 4) {
		fmt.Printf("        Case 1: TOP_A, size=3, consecutive 4, calling sortThree\n")
		sortThree(ps, max)
		return
	}
	
	if max.Loc == stack.TOP_A && a.GetValueAtPosition(1) == a.GetValueAtPosition(3)-1 && 
		aPartlySort(ps, 3) {
		fmt.Printf("        Case 2: TOP_A, A[0]==A[2]-1, swapping and reducing size\n")
		stack.Swap_a(ps)
		max.Size--
		fmt.Printf("        After Case 2: max size=%d\n", max.Size)
	}
	
	if max.Loc == stack.TOP_A && aPartlySort(ps, 1) {
		fmt.Printf("        Case 3: TOP_A, partly sorted from 1, reducing size\n")
		max.Size--
		fmt.Printf("        After Case 3: max size=%d\n", max.Size)
	}
	
	fmt.Printf("      splitMaxReduction end: max size=%d\n", max.Size)
}

// aPartlySort checks if stack A is partially sorted from a given position (exactly like C implementation)
func aPartlySort(ps *stack.PushSwapData, from int) bool {
	fmt.Printf("        aPartlySort: checking from position %d\n", from)
	
	a := ps.A
	
	// Start from the top position like C implementation
	i := a.GetTop()
	fmt.Printf("          Starting from top position: %d\n", i)
	
	// Move down 'from' positions like C: while (--from) i = next_down(a, i);
	for from > 1 {
		i = a.NextDown(i)
		from--
		fmt.Printf("          Moved down to position: %d\n", i)
	}
	
	// Check if values are consecutive going down like C implementation
	fmt.Printf("          Checking consecutive values from position %d\n", i)
	for a.Value(i) != a.Size() {
		value := a.Value(i)
		i = a.NextDown(i)
		if a.Value(i) != value+1 {
			fmt.Printf("          Not consecutive: %d != %d+1\n", a.Value(i), value)
			return false
		}
		fmt.Printf("          Consecutive: %d, %d\n", value, a.Value(i))
	}
	
	fmt.Printf("          aPartlySort result: true\n")
	return true
}

// isConsecutive checks if four numbers are consecutive (exactly like C implementation)
func isConsecutive(a, b, c, d int) bool {
	fmt.Printf("          isConsecutive: checking %d, %d, %d, %d\n", a, b, c, d)
	
	// Sort only the first three numbers, like C implementation
	sortThreeNumbers(&a, &b, &c)
	fmt.Printf("          After sorting first three: %d, %d, %d\n", a, b, c)
	
	result := (b-a == 1) && (c-b == 1) && (d-c == 1)
	fmt.Printf("          isConsecutive result: %t\n", result)
	return result
}

// sortThreeNumbers sorts three numbers in ascending order (exactly like C implementation)
func sortThreeNumbers(a, b, c *int) {
	fmt.Printf("            sortThreeNumbers: %d, %d, %d\n", *a, *b, *c)
	
	if *a > *b {
		temp := *a
		*a = *b
		*b = temp
		fmt.Printf("              Swapped a,b: %d, %d, %d\n", *a, *b, *c)
	}
	if *a > *c {
		temp := *a
		*a = *c
		*c = temp
		fmt.Printf("              Swapped a,c: %d, %d, %d\n", *a, *b, *c)
	}
	if *b > *c {
		temp := *b
		*b = *c
		*c = temp
		fmt.Printf("              Swapped b,c: %d, %d, %d\n", *a, *b, *c)
	}
	
	fmt.Printf("            Final result: %d, %d, %d\n", *a, *b, *c)
}
