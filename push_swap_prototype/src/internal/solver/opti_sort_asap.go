package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

func SplitMaxReduction(ps *ops.SortingState, max *chunk.Chunk) {

	a := ps.A

	if max.Loc == chunk.TOP_A && max.Size == 3 && isConsecutive(
		stack.GetValue(a, 1), stack.GetValue(a, 2),
		stack.GetValue(a, 3), stack.GetValue(a, 4)) &&
		APartlySort(ps, 4) {
		SortThree(ps, max)
		return
	}

	if max.Loc == chunk.TOP_A && stack.GetValue(a, 1) == stack.GetValue(a, 3)-1 &&
		APartlySort(ps, 3) {
		ops.SwapA(ps)
		max.Size--
	}

	if max.Loc == chunk.TOP_A && APartlySort(ps, 1) {
		max.Size--
	}
}

func APartlySort(ps *ops.SortingState, from int) bool {
	
	a := ps.A

	i := stack.GetTop(a)

	for ; from > 0; from-- {
		i = stack.Next(a, i)
	}
	
	value := stack.GetValue(a, i) // Initialize value with first element
	for ; stack.GetValue(a, i) != stack.GettSize(a); i = stack.Next(a, i) {  // FIXED: Use ps.A.Size like C implementation (data->a.size)
		if stack.GetValue(a, i) != value + 1 {
			return false
		}
		value = stack.GetValue(a, i) // FIXED: Update value in each iteration like C implementation
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
		*a, *b = *b, *a
	}
	if *a > *c {
		*a, *c = *c, *a
	}
	if *b > *c {
		*b, *c = *c, *b
	}
}
