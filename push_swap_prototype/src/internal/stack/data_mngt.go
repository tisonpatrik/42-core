package stack

func InitData(numbers []int, writing_mode bool) *PushSwapData {
	stack_a := InitStack(len(numbers))
	stack_b := InitStack(len(numbers))
	FillStack(stack_a, numbers)
	ps := &PushSwapData{
		A: stack_a,
		B: stack_b,
		OpList: make([]Operation, 0),
		WritingMode: writing_mode,
	}
	return ps
}

func InitStack(size int) *Stack {
	stack := &Stack{
		Stack:  make([]int, size),
		Size:   size,
		Top:    0,
		Bottom: 0,
	}
	
	for i := range stack.Stack {
		stack.Stack[i] = 0
	}
	
	return stack
}



func IsSorted(ps *PushSwapData) bool {
	i := ps.A.Top
	rank := 1

	for rank <= ps.A.Size {
		if ps.A.Stack[i] != rank {
			return false
		}
		rank++
		i = NextDown(ps.A, i)
	}
	return true
}

