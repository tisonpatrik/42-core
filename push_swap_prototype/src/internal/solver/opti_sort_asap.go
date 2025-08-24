package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

func SplitMaxReduction(ps *stack.PushSwapData, max *stack.Chunk) {
	fmt.Printf("DEBUG: SplitMaxReduction START - max: loc=%v, size=%d\n", max.Loc, max.Size)

	a := ps.A

	if max.Loc == stack.TOP_A && max.Size == 3 && isConsecutive(
		a.GetValueAtPosition(1), a.GetValueAtPosition(2),
		a.GetValueAtPosition(3), a.GetValueAtPosition(4)) &&
		APartlySort(ps, 4) {
		fmt.Printf("DEBUG: SplitMaxReduction - Case 1: Sorting 3 consecutive elements\n")
		SortThree(ps, max)
		fmt.Printf("DEBUG: SplitMaxReduction - After SortThree: max.Size=%d\n", max.Size)
		return
	}

	if max.Loc == stack.TOP_A && a.GetValueAtPosition(1) == a.GetValueAtPosition(3)-1 &&
		APartlySort(ps, 3) {
		fmt.Printf("DEBUG: SplitMaxReduction - Case 2: Swapping and decrementing size (size: %d->", max.Size)
		stack.Swap_a(ps)
		max.Size--
		fmt.Printf("%d)\n", max.Size)
	}

	if max.Loc == stack.TOP_A && APartlySort(ps, 1) {
		fmt.Printf("DEBUG: SplitMaxReduction - Case 3: Decrementing size (size: %d->", max.Size)
		max.Size--
		fmt.Printf("%d)\n", max.Size)
	}

	fmt.Printf("DEBUG: SplitMaxReduction END - max.Size=%d\n", max.Size)
}

func APartlySort(ps *stack.PushSwapData, from int) bool {
	a := ps.A

	if from <= 0 {
        // defensive: v C by sem nešlo z validních volání
        return false
    }
	fmt.Printf("DEBUG: APartlySort START - from=%d, stack_capacity=%d, current_size=%d\n", from, a.Size(), a.CurrentSize())

	i := a.GetTop()
	fmt.Printf("DEBUG: APartlySort - initial i=%d, value=%d, top=%d, bottom=%d\n", i, a.Value(i), a.GetTop(), a.GetBottom())

	for from > 1 {
		from--
		i = a.NextDown(i)
		fmt.Printf("DEBUG: APartlySort - after moving down: i=%d, value=%d\n", i, a.Value(i))
	}
	maxValue := a.Size()
	if maxValue <= 0 {
        return false
    }

	fmt.Printf("DEBUG: APartlySort - starting loop: i=%d, value=%d, maxValue=%d\n", i, a.Value(i), maxValue)
	
    for a.Value(i) != maxValue {
        v := a.Value(i)
        fmt.Printf("DEBUG: APartlySort LOOP - i=%d, value=%d, maxValue=%d\n", i, v, maxValue)
        
        next := a.NextDown(i)
        fmt.Printf("DEBUG: APartlySort LOOP - next=%d, next_value=%d, expected=%d\n", next, a.Value(next), v+1)
        
        if a.Value(next) != v+1 {
            fmt.Printf("DEBUG: APartlySort - returning false: %d != %d\n", a.Value(next), v+1)
            return false
        }
        i = next
        
        // Safety check to prevent infinite loops
        if i < 0 || i >= a.Size() {
            fmt.Printf("DEBUG: APartlySort - index out of bounds: i=%d, size=%d\n", i, a.Size())
            return false
        }
    }
    
    fmt.Printf("DEBUG: APartlySort - returning true\n")
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
