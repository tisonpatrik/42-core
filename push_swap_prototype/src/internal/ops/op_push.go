package ops

import (
	"push_swap_prototype/internal/stack"
)

func push(src, dest *stack.Stack) bool {
	if stack.GetSize(src) == 0 {
		return false
	}
	v := stack.Pop(src)
	stack.Push(dest, v.GetContent())
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