package stack

// NextUp returns the next index going up in the stack
// Equivalent to next_up in C implementation
func (s *Stack) NextUp(index int) int {
	if s.CurrentSize() == 0 {
		return index
	}
	if index < 0 || index >= s.size {
		return index
	}
	if index == 0 {
		return s.size - 1
	} else {
		return index - 1
	}
}

// NextDown returns the next index going down in the stack
// Equivalent to next_down in C implementation
func (s *Stack) NextDown(index int) int {
	if s.CurrentSize() == 0 {
		return index
	}
	if index < 0 || index >= s.size {
		return index
	}
	if index == s.size-1 {
		return 0
	} else {
		return index + 1
	}
}

// GetValueAtPosition returns the value at a specific position (1-based like C)
// Equivalent to value in C implementation
func (s *Stack) GetValueAtPosition(pos int) int {
	if s.CurrentSize() == 0 {
		return 0
	}
	index := s.top
	for i := 1; i < pos; i++ {
		index = s.NextDown(index)
	}
	if index < 0 || index >= len(s.stack) {
		return 0
	}
	return s.stack[index]
}

// CurrentSize returns the current number of elements in the stack
// Equivalent to current_size in C implementation
func (s *Stack) CurrentSize() int {
	// Check if stack is empty or uninitialized
	if s.size == 0 || len(s.stack) == 0 {
		return 0
	}

	if s.top == s.bottom && s.stack[s.top] == 0 {
		return 0
	}
	if s.top > s.bottom {
		return ((s.size - s.top) + (s.bottom + 1))
	} else {
		return (s.bottom - s.top + 1)
	}
}

// IsFull returns true if the stack is at maximum capacity
// Equivalent to is_full in C implementation
func (s *Stack) IsFull() bool {

	return s.size == s.CurrentSize()
}
