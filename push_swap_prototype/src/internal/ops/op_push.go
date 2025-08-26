package ops

import (
	"push_swap_prototype/internal/stack"
)

func push(src *stack.Stack, dest *stack.Stack) bool {
	if stack.IsFull(dest) {
		return false
	}
	
	// Check if source is empty
	if stack.GetSize(src) == 0 {
		return false
	}
	
	// Get the top value from source stack using Peek
	topValuePtr := stack.Peek(src)
	if topValuePtr == nil {
		return false
	}
	
	value := *topValuePtr
	
	// Push to destination using existing stack.Push
	stack.Push(dest, value)
	
	// Remove from source using existing stack.Pop
	stack.Pop(src)
	
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