package stack

// FillStack fills a stack with values from a slice (like C fill_stack)
func FillStack(s *Stack, values []int) {
	s.Stack = values
	s.Bottom = s.Size - 1
}