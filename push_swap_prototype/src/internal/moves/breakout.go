package moves

import "push_swap_prototype/internal/stack"

// BreakpointsCyclicA spočítá, kolikrát v A (včetně wrapu last->first) platí A[i] > A[i+1].
// To je užitečná jako hrubá heuristika "jak daleko jsme od cyklického vzestupného pořadí".
func BreakpointsCyclicA(a *stack.Stack) int {
	size := stack.GetSize(a)
	if size <= 1 {
		return 0
	}
	// naštíti hodnoty do slice (top->bottom)
	vals := make([]int, 0, size)
	for n := stack.GetHead(a); n != nil; n = n.GetNext() {
		vals = append(vals, n.GetContent()) // uprav Value podle tvého názvu pole
	}

	br := 0
	for i := 0; i < size-1; i++ {
		if vals[i] > vals[i+1] {
			br++
		}
	}
	// wrap last -> first
	if vals[size-1] > vals[0] {
		br++
	}
	return br
}
