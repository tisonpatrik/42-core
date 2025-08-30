package moves

import "push_swap_prototype/internal/stack"

// BreakpointsCyclicA spo\u010d�t�, kolikr�t v A (v\u010detn\u011b wrapu last->first) plat� A[i] > A[i+1].
// To je u\u017eite\u010dn� jako hrub� heuristika "jak daleko jsme od cyklick�ho vzestupn�ho po\u0159ad�".
func BreakpointsCyclicA(a *stack.Stack) int {
	size := stack.GetSize(a)
	if size <= 1 {
		return 0
	}
	// na\u010dti hodnoty do slice (top->bottom)
	vals := make([]int, 0, size)
	for n := stack.GetHead(a); n != nil; n = n.GetNext() {
		vals = append(vals, n.GetContent()) // uprav Value podle tv�ho n�zvu pole
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
