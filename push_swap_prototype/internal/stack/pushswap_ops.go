package stack

// SwapTop swaps the top two elements of a stack
func (s *Stack) SwapTop() bool {
	if s.length < 2 {
		return false
	}
	
	// For circular doubly-linked list, we need to handle the case where length == 2 specially
	if s.length == 2 {
		// Just swap head and the other node
		s.head = s.head.Next
		return true
	}
	
	// Swap the top two nodes
	first := s.head
	second := s.head.Next
	
	// Update the links
	first.Prev.Next = second
	second.Next.Prev = first
	
	first.Next = second.Next
	second.Prev = first.Prev
	
	first.Prev = second
	second.Next = first
	
	s.head = second
	
	return true
}

// RotateUp rotates the stack up (top element goes to bottom) - O(1) operation
func (s *Stack) RotateUp() bool {
	if s.length < 2 {
		return false
	}
	
	// Simply move head to next element
	s.head = s.head.Next
	return true
}

// RotateDown rotates the stack down (bottom element goes to top) - O(1) operation
func (s *Stack) RotateDown() bool {
	if s.length < 2 {
		return false
	}
	
	// Simply move head to previous element
	s.head = s.head.Prev
	return true
}

// Pop removes and returns the top element
func (s *Stack) Pop() *Node {
	if s.length == 0 {
		return nil
	}
	
	node := s.head
	if s.length == 1 {
		s.head = nil
	} else {
		s.head.Prev.Next = s.head.Next
		s.head.Next.Prev = s.head.Prev
		s.head = s.head.Next
	}
	
	node.Next = nil
	node.Prev = nil
	s.length--
	return node
}

// PushFrom pushes an element from another stack to this stack
func (s *Stack) PushFrom(other *Stack) bool {
	if other.length == 0 {
		return false
	}
	
	// Pop from other stack
	node := other.Pop()
	if node == nil {
		return false
	}
	
	// Push to this stack
	s.PushNode(node)
	return true
}

// GetValueAtPosition returns the value at a specific position
func (s *Stack) GetValueAtPosition(pos int) int {
	if pos < 0 || pos >= s.length {
		return 0
	}
	
	current := s.head
	for i := 0; i < pos; i++ {
		current = current.Next
	}
	return current.Val
}

// GetIdxAtPosition returns the index at a specific position
func (s *Stack) GetIdxAtPosition(pos int) int {
	if pos < 0 || pos >= s.length {
		return -1
	}
	
	current := s.head
	for i := 0; i < pos; i++ {
		current = current.Next
	}
	return current.Idx
}




