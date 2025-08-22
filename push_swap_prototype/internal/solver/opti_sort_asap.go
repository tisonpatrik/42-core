package solver

import (
	"push_swap_prototype/internal/stack"
)

func splitMaxReduction(ps *stack.PushSwapData, max *stack.Chunk) {
	a := ps.A
	
	if max.Loc == stack.TOP_A && max.Size == 3 && isConsecutive(
		a.GetValueAtPosition(1), a.GetValueAtPosition(2), 
		a.GetValueAtPosition(3), a.GetValueAtPosition(4)) && 
		aPartlySort(ps, 4) {
		sortThree(ps, max)
		return
	}
	
	if max.Loc == stack.TOP_A && a.GetValueAtPosition(1) == a.GetValueAtPosition(3)-1 && 
		aPartlySort(ps, 3) {
		stack.Swap_a(ps)
		max.Size--
	}
	
	if max.Loc == stack.TOP_A && aPartlySort(ps, 1) {
		max.Size--
	}
	
}

func aPartlySort(ps *stack.PushSwapData, from int) bool {
	
	a := ps.A
	
	i := a.GetTop()
	
	for from > 1 {
		from--
		i = a.NextDown(i)
	}
	
	for a.Value(i) != a.Size() {
		value := a.Value(i)
		i = a.NextDown(i)
		if a.Value(i) != value+1 {
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
