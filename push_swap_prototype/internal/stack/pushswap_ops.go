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

// PushFrom pushes an element from another stack to this stack (exactly like C push)
func (s *Stack) PushFrom(other *Stack) bool {
	if other.CurrentSize() == 0 {
		return false
	}
	
	// If destination is empty, initialize it with sufficient capacity
	if s.size == 0 {
		// Initialize with size equal to source size to avoid expansion issues
		s.stack = make([]int, other.size)
		s.size = other.size
		s.top = 0
		s.bottom = 0
		
		// For empty destination, first element goes at top
		s.stack[s.top] = other.stack[other.top]
		other.stack[other.top] = 0
		other.top = other.NextDown(other.top)
		return true
	}
	
	// If destination is full, return false (like C implementation)
	if s.IsFull() {
		return false
	}
	
	// Exactly like C push operation
	destIndex := s.NextUp(s.top)
	s.stack[destIndex] = other.stack[other.top]
	s.top = destIndex
	other.stack[other.top] = 0
	other.top = other.NextDown(other.top)
	
	return true
}

