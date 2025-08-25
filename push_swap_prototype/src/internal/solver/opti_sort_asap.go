package solver

import (
	"push_swap_prototype/internal/stack"
)

func SplitMaxReduction(ps *stack.PushSwapData, max *stack.Chunk) {

	a := ps.A

	if max.Loc == stack.TOP_A && max.Size == 3 && isConsecutive(
		a.GetValue(1), a.GetValue(2),
		a.GetValue(3), a.GetValue(4)) &&
		APartlySort(ps, 4) {
		SortThree(ps, max)
		return
	}

	if max.Loc == stack.TOP_A && a.GetValue(1) == a.GetValue(3)-1 &&
		APartlySort(ps, 3) {
		stack.Swap_a(ps)
		max.Size--
	}

	if max.Loc == stack.TOP_A && APartlySort(ps, 1) {
		max.Size--
	}
}

func APartlySort(ps *stack.PushSwapData, from int) bool {
	
	a := ps.A
	
	// Fix: Start from top and advance by (from-1) positions (like C implementation)
	i := a.GetTop()
	
	// Fix: Decrement from BEFORE using it (like C: while (--from))
	for from > 1 {
		from--
		i = a.NextDown(i)
	}
	
	// Fix: Check bounds before accessing
	if i < 0 || i >= len(a.GetStack()) {
		return false
	}
	
	// Fix: Check if we've reached the end of the stack
	for i >= 0 && a.GetStack()[i] != ps.A.Size() {
		value := a.GetStack()[i]
		i = a.NextDown(i)
		
		// Fix: Check bounds before next access
		if i < 0 || i >= len(a.GetStack()) {
			return false
		}
		
		nextValue := a.GetStack()[i]
		
		if nextValue != value+1 {
			return false
		}
	}
	
	return true
}

func isConsecutive(a, b, c, d int) bool {

	sortThreeNumbers(&a, &b, &c)

	result := (b-a == 1) && (c-b == 1) && (d-c == 1)
	return result
}

func sortThreeNumbers(a, b, c *int) {
	
	// Optimalizovaný algoritmus pro 3 čísla - méně porovnání a swapů
	if *a > *b {
		*a, *b = *b, *a
	}
	if *b > *c {
		*b, *c = *c, *b
		// Po swapu b a c musíme zkontrolovat a a b
		if *a > *b {
			*a, *b = *b, *a
		}
	}
}
