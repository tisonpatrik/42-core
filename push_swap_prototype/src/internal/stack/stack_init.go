package stack

// New creates a new empty stack
func New() *Stack {
	return &Stack{
		Stack:  []int{},
		Size:   0,
		Top:    0,
		Bottom: 0,
	}
}

// FillStack fills a stack with values from a slice (like C fill_stack)
func FillStack(s *Stack, values []int) {
	s.Stack = values
	s.Bottom = s.Size - 1
}