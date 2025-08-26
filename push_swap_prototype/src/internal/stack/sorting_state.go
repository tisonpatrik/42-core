package stack

type SortingState struct {
	A           *Stack
	B           *Stack
	OpList      []Operation
	WritingMode bool
}

func InitData(numbers []int) *SortingState {
	stack_a := InitStack(len(numbers))
	stack_b := InitStack(len(numbers))
	FillStack(stack_a, numbers)
	ps := &SortingState{
		A: stack_a,
		B: stack_b,
		OpList: make([]Operation, 0),
	}
	return ps
}

