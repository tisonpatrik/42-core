package stack

// SwapTop swaps the top two elements of a stack
func (s *Stack) SwapTop() bool {
	if s.CurrentSize() < 2 {
		return false
	}

	// Get the second element position using NextDown like C implementation
	secondPos := s.NextDown(s.top)

	// Swap the top two elements
	s.stack[s.top], s.stack[secondPos] = s.stack[secondPos], s.stack[s.top]
	return true
}

// RotateUp rotates the stack up (top element goes to bottom) - exactly like C rotate
func (s *Stack) RotateUp() bool {
	// C implementation always performs rotate operation regardless of stack size
	// But we need to handle empty stacks to avoid panics
	if s.CurrentSize() == 0 {
		// Empty stack - just return true (like C would)
		return true
	}

	if s.IsFull() {
		s.bottom = s.top
		s.top = s.NextDown(s.top)
	} else {
		s.bottom = s.NextDown(s.bottom)
		s.stack[s.bottom] = s.stack[s.top]
		s.stack[s.top] = 0
		s.top = s.NextDown(s.top)
	}
	return true
}

// RotateDown rotates the stack down (bottom element goes to top) - exactly like C r_rotate
func (s *Stack) RotateDown() bool {
	// C implementation always performs r_rotate operation regardless of stack size
	// But we need to handle empty stacks to avoid panics
	if s.CurrentSize() == 0 {
		// Empty stack - just return true (like C would)
		return true
	}

	if s.IsFull() {
		s.top = s.bottom
		s.bottom = s.NextUp(s.bottom)
	} else {
		s.top = s.NextUp(s.top)
		s.stack[s.top] = s.stack[s.bottom]
		s.stack[s.bottom] = 0
		s.bottom = s.NextUp(s.bottom)
	}
	return true
}

func (s *Stack) PushFrom(other *Stack) bool {
	// C implementation only checks if destination is full
	if s.IsFull() {
		return false
	}

	// C implementation doesn't check if source is empty
	if other.CurrentSize() == 0 {
		return true
	}

	// If destination is empty, initialize it with sufficient capacity
	if s.CurrentSize() == 0 {
		// FIXED: Don't change s.size (capacity), just ensure capacity
		if cap(s.stack) < 1 {
			s.stack = make([]int, 100) // Ensure sufficient capacity
		}
		
		// For empty destination, first element goes at top
		s.stack[s.top] = other.stack[other.top]
		other.stack[other.top] = 0
		other.top = other.NextDown(other.top)
		
		// FIXED: Don't change s.size, it's the capacity
		return true
	}

	// Exactly like C push operation
	destIndex := s.NextUp(s.top)
	s.stack[destIndex] = other.stack[other.top]
	s.top = destIndex
	other.stack[other.top] = 0
	other.top = other.NextDown(other.top)
	
	// FIXED: Don't change s.size, it's the capacity
	return true
}