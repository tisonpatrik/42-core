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

func PushA(ps *SortingState) {

	operationSucceeded := push(ps.B, ps.A)
	if operationSucceeded {
		SaveOp(ps, PA)
	}
}

func PushB(ps *SortingState) {

	operationSucceeded := push(ps.A, ps.B)
	if operationSucceeded {
		SaveOp(ps, PB)
	}
}