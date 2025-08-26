package stack

func NewPushSwapData() *SortingState {
	return &SortingState{
		A: &Stack{
			Stack:  []int{},
			capacity:   0,
			Top:    0,
			Bottom: 0,
		},
		B: &Stack{
			Stack:  []int{},
			capacity:   0,
			Top:    0,
			Bottom: 0,
		},
	}
}

// InitStacks initializes both stacks with the given size (like C init_stack)
func InitStacks(ps *SortingState, size int) {
	// Initialize stack A
	ps.A.capacity = size
	ps.A.Stack = make([]int, size)
	for i := range ps.A.Stack {
		ps.A.Stack[i] = 0
	}
	
	// Initialize stack B (same as C implementation)
	ps.B.capacity = size
	ps.B.Stack = make([]int, size)
	for i := range ps.B.Stack {
		ps.B.Stack[i] = 0
	}
}


func SaveOp(ps *SortingState, op Operation) {
	ps.OpList = append(ps.OpList, op)
}


