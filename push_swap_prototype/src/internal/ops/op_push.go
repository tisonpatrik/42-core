package ops

import (
	"push_swap_prototype/internal/stack"
)

func push(src, dest *stack.Stack) bool {
	if stack.IsFull(dest) || stack.GetSize(src) == 0 {
		return false
	}
	v := stack.Pop(src)                  // safe: src has at least 1 element
	if v == stack.NullValue() {          // defensively, we should not get here
		return false
	}
	stack.Push(dest, v)                  // safe: dest is not full
	return true
}

// Take the first element at the top of b and put it at the top of a.
// Do nothing if b is empty.
func PushA(ps *SortingState) {

	operationSucceeded := push(ps.B, ps.A)
	if operationSucceeded {
		SaveOp(ps, PA)
	}
}

//Take the first element at the top of a and put it at the top of b.
//Do nothing if a is empty.
func PushB(ps *SortingState) {

	operationSucceeded := push(ps.A, ps.B)
	if operationSucceeded {
		SaveOp(ps, PB)
	}
}