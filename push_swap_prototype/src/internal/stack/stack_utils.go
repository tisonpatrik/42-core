package stack

// Push adds a value to the top of the stack
func Push(s *Stack, value int)*Node  {
	if value < 0 {
		panic("Cannot push negative numbers")
	}

	newNode := CreateNode(value)
	
	if s.size == 0 {
		s.head = newNode
		s.tail = newNode
	} else {
		newNode.next = s.head
		s.head.prev = newNode
		s.head = newNode
	}
	
	s.size++
	return newNode
}

// Peek returns the top element without removing it
func Peek(s *Stack) *int {
	if s.size == 0 {
		return nil
	}
	return &s.head.content
}

// Pop removes and returns the top element
func Pop(s *Stack) int {
	if s.size == 0 {
		return -1
	}

	value := s.head.content
	
	if s.size == 1 {
		// last element -> empty stack
		s.head = nil
		s.tail = nil
	} else {
		// move head to next element
		s.head = s.head.next
		s.head.prev = nil
	}
	
	s.size--
	return value
}

// Rotate moves the top element to the bottom
func Rotate(s *Stack) bool {
	if s.size <= 1 {
		return false
	}
	
	// take value from top
	topNode := s.head
	
	// move head to next element
	s.head = s.head.next
	s.head.prev = nil
	
	// add old top to bottom
	topNode.next = nil
	topNode.prev = s.tail
	s.tail.next = topNode
	s.tail = topNode
	
	return true
}

// ReverseRotate moves the bottom element to the top
func ReverseRotate(s *Stack) bool {
	if s.size <= 1 {
		return false
	}
	
	// take value from bottom
	bottomNode := s.tail
	
	// move tail to previous element
	s.tail = s.tail.prev
	s.tail.next = nil
	
	// add old bottom to top
	bottomNode.prev = nil
	bottomNode.next = s.head
	s.head.prev = bottomNode
	s.head = bottomNode
	
	return true
}

// Swap exchanges the first two elements
func Swap(s *Stack) bool {
	if s.size < 2 {
		return false
	}
	
	// swap content of first two nodes
	s.head.content, s.head.next.content = s.head.next.content, s.head.content
	return true
}

// IsSorted checks if the stack is sorted in ascending order
func IsSorted(s *Stack) bool {
	if s.size <= 1 {
		return true
	}
	
	current := s.head
	next := current.next
	
	for next != nil {
		if current.content > next.content {
			return false
		}
		current = next
		next = next.next
	}
	return true
}

// FillStack fills the stack with given values
func FillStack(s *Stack, values []int) {
	if s == nil {
		panic("Stack is nil")
	}
	
	// Clear existing stack
	ClearStack(s)
	
	// Add new values (they will be added in reverse order due to Push)
	// So we need to add them in reverse to maintain original order
	for i := len(values) - 1; i >= 0; i-- {
		if values[i] < 0 {
			panic("Cannot push negative numbers")
		}
		Push(s, values[i])
	}
}

// FindMinMaxPos finds position of min or max value
func FindMinMaxPos(s *Stack, findMax bool) int {
	if s.size == 0 {
		return -1
	}
	
	current := s.head
	pos := 0
	bestPos := 0
	bestValue := current.content
	
	for i := 0; i < s.size; i++ {
		if findMax && current.content > bestValue {
			bestValue = current.content
			bestPos = pos
		} else if !findMax && current.content < bestValue {
			bestValue = current.content
			bestPos = pos
		}
		current = current.next
		pos++
	}
	
	return bestPos
}

// GetNodeAt returns the node at a specific position
func GetNodeAt(s *Stack, pos int) *Node {
	if pos < 0 || pos >= s.size {
		return nil
	}
	
	current := s.head
	for i := 0; i < pos; i++ {
		current = current.next
	}
	return current
}

// IsSortedAscending checks if stack is sorted in ascending order
func IsSortedAscending(s *Stack) bool {
	if s.size <= 1 {
		return true
	}
	
	current := s.head
	next := current.next
	
	for next != nil {
		if current.content > next.content {
			return false
		}
		current = next
		next = next.next
	}
	return true
}

// IsSortedDescending checks if stack is sorted in descending order
func IsSortedDescending(s *Stack) bool {
	if s.size <= 1 {
		return true
	}
	
	current := s.head
	next := current.next
	
	for next != nil {
		if current.content < next.content {
			return false
		}
		current = next
		next = next.next
	}
	return true
}

// FindTarget finds the best position to insert a value in a sorted stack
func FindTarget(s *Stack, value int) int {
	if s.size == 0 {
		return 0
	}
	
	current := s.head
	pos := 0
	
	for pos < s.size {
		if value < current.content {
			return pos
		}
		current = current.next
		pos++
	}
	
	return s.size
}

// GetMinMaxValue returns the minimum or maximum value in the stack
func GetMinMaxValue(s *Stack, findMax bool) int {
	if s.size == 0 {
		return -1
	}
	
	current := s.head
	bestValue := current.content
	
	for i := 1; i < s.size; i++ {
		current = current.next
		if findMax && current.content > bestValue {
			bestValue = current.content
		} else if !findMax && current.content < bestValue {
			bestValue = current.content
		}
	}
	
	return bestValue
}

// GetMinMaxPosition returns the position of minimum or maximum value
func GetMinMaxPosition(s *Stack, findMax bool) int {
	if s.size == 0 {
		return -1
	}
	
	current := s.head
	bestPos := 0
	bestValue := current.content
	
	for i := 1; i < s.size; i++ {
		current = current.next
		if findMax && current.content > bestValue {
			bestValue = current.content
			bestPos = i
		} else if !findMax && current.content < bestValue {
			bestValue = current.content
			bestPos = i
		}
	}
	
	return bestPos
}
