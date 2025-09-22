package selector

import (
	"push_swap_prototype/internal/stack"
)

// RemoveElementAt removes an element at the specified index from a slice
func RemoveElementAt(s []int, i int) []int {
	out := make([]int, 0, len(s)-1)
	out = append(out, s[:i]...)
	out = append(out, s[i+1:]...)
	return out
}

// InsertElementAt inserts an element at the specified index into a slice
func InsertElementAt(s []int, i, x int) []int {
	out := make([]int, 0, len(s)+1)
	out = append(out, s[:i]...)
	out = append(out, x)
	out = append(out, s[i:]...)
	return out
}

// SnapshotStack converts a stack to a slice representation for efficient processing
func SnapshotStack(s *stack.Stack) []int {
	out := make([]int, 0, stack.GetSize(s))
	for n := stack.GetHead(s); n != nil; n = n.GetNext() {
		out = append(out, n.GetContent())
	}
	return out
}

// CalculateBreakpoints calculates the number of breakpoints in a cyclic array
func CalculateBreakpoints(a []int) int {
	if IsEmptyOrSingle(a) {
		return 0
	}
	
	n := len(a)
	breakpoints := 0
	for i := 0; i < n-1; i++ {
		if a[i] > a[i+1] {
			breakpoints++
		}
	}
	if a[n-1] > a[0] {
		breakpoints++
	}
	return breakpoints
}
