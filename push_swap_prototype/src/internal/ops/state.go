package ops

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

type SortingState struct {
	A           *stack.Stack
	B           *stack.Stack
	OpList      []Operation
}

func InitData(numbers []int) *SortingState {
	stack_a := stack.InitStack()
	stack_b := stack.InitStack()
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

// PrintOps prints each operation on its own line
func (ps *SortingState) PrintOps() {
	for _, op := range ps.OpList {
		fmt.Println(op.String())
	}
}

// String returns the string representation of an Operation
func (op Operation) String() string {
	switch op {
	case SA:
		return "sa"
	case SB:
		return "sb"
	case SS:
		return "ss"
	case PA:
		return "pa"
	case PB:
		return "pb"
	case RA:
		return "ra"
	case RB:
		return "rb"
	case RR:
		return "rr"
	case RRA:
		return "rra"
	case RRB:
		return "rrb"
	case RRR:
		return "rrr"
	default:
		return "unknown"
	}
}


