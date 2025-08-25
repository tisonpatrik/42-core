package stack

func NewPushSwapData() *PushSwapData {
	return &PushSwapData{
		A: &Stack{
			Stack:  []int{},
			Size:   0,
			Top:    0,
			Bottom: 0,
		},
		B: &Stack{
			Stack:  []int{},
			Size:   0,
			Top:    0,
			Bottom: 0,
		},
	}
}

// InitStacks initializes both stacks with the given size (like C init_stack)
func InitStacks(ps *PushSwapData, size int) {
	// Initialize stack A
	ps.A.Size = size
	ps.A.Stack = make([]int, size)
	for i := range ps.A.Stack {
		ps.A.Stack[i] = 0
	}
	
	// Initialize stack B (same as C implementation)
	ps.B.Size = size
	ps.B.Stack = make([]int, size)
	for i := range ps.B.Stack {
		ps.B.Stack[i] = 0
	}
}


func SaveOp(ps *PushSwapData, op Operation) {
	ps.OpList = append(ps.OpList, op)
}


