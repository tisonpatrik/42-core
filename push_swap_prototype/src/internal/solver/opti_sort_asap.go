package solver

import (
	"push_swap_prototype/internal/stack"
)

func SplitMaxReduction(ps *stack.PushSwapData, max *stack.Chunk) {

	a := ps.A

	if max.Loc == stack.TOP_A && max.Size == 3 && isConsecutive(
		stack.Value(a, 1), stack.Value(a, 2),
		stack.Value(a, 3), stack.Value(a, 4)) &&
		APartlySort(ps, 4) {
		SortThree(ps, max)
		return
	}

	if max.Loc == stack.TOP_A && stack.Value(a, 1) == stack.Value(a, 3)-1 &&
		APartlySort(ps, 3) {
		stack.SwapA(ps)
		max.Size--
	}

	if max.Loc == stack.TOP_A && APartlySort(ps, 1) {
		max.Size--
	}
}

func APartlySort(ps *stack.PushSwapData, from int) bool {
	
	a := ps.A

	i := a.Top

	for ; from > 0; from-- {
		i = stack.NextDown(a, i)
	}
	
	value := a.Stack[i] // Initialize value with first element
	for ; a.Stack[i] != ps.A.Size; i = stack.NextDown(a, i) {  // FIXED: Use ps.A.Size like C implementation (data->a.size)
		if a.Stack[i] != value + 1 {
			return false
		}
		value = a.Stack[i] // FIXED: Update value in each iteration like C implementation
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
