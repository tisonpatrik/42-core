package ops

import (
	"push_swap_prototype/internal/stack"
)

type SortingState struct {
	A           *stack.Stack
	B           *stack.Stack
	OpList      []Operation
}

func InitData(numbers []int) *SortingState {
	stack_a := stack.InitStack(len(numbers))
	stack_b := stack.InitStack(len(numbers))
	stack.FillStack(stack_a, numbers)
	ps := &SortingState{
		A: stack_a,
		B: stack_b,
		OpList: make([]Operation, 0),
	}
	return ps
}

func SaveOp(ps *SortingState, op Operation) {
	ps.OpList = append(ps.OpList, op)
}


