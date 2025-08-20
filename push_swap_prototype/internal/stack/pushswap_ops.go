package stack

// SwapTop swaps the top two elements of a stack
func (s *Stack) SwapTop() bool {
	if s.length < 2 {
		return false
	}
	
	// Swap the top two nodes
	first := s.top
	second := s.top.prev
	
	// Update links
	s.top = second
	second.prev = first.prev
	first.prev = second
	
	return true
}

// RotateUp rotates the stack up (top element goes to bottom)
func (s *Stack) RotateUp() bool {
	if s.length < 2 {
		return false
	}
	
	// Find the bottom node
	current := s.top
	for current.prev != nil {
		current = current.prev
	}
	
	// Move top to bottom
	top := s.top
	s.top = top.prev
	top.prev = nil
	current.prev = top
	
	return true
}

// RotateDown rotates the stack down (bottom element goes to top)
func (s *Stack) RotateDown() bool {
	if s.length < 2 {
		return false
	}
	
	// Find second to last node
	current := s.top
	for current.prev != nil && current.prev.prev != nil {
		current = current.prev
	}
	
	// Move bottom to top
	if current.prev != nil {
		bottom := current.prev
		current.prev = nil
		bottom.prev = s.top
		s.top = bottom
	}
	
	return true
}

// PushFrom pushes an element from another stack to this stack
func (s *Stack) PushFrom(other *Stack) bool {
	if other.length == 0 {
		return false
	}
	
	// Pop from other stack
	value := other.Pop()
	s.Push(value)
	return true
}
