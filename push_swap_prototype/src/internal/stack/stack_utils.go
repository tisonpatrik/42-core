package stack

import "math"

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


// Pop removes and returns the top element
func Pop(s *Stack) *Node {
	if s.size == 0 {
		return nil
	}

	node := s.head
	
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
	return node
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

// GetMin returns the minimum value in the stack
func GetMin(s *Stack) int {
	if IsEmpty(s) {
		return 0
	}
	
	current := GetHead(s)
	min := current.GetContent()
	
	for i := 0; i < GetSize(s); i++ {
		if current.GetContent() < min {
			min = current.GetContent()
		}
		current = current.GetNext()
	}
	
	return min
}

// GetMax returns the maximum value in the stack
func GetMax(s *Stack) int {
	if IsEmpty(s) {
		return 0
	}
	
	current := GetHead(s)
	max := current.GetContent()
	
	for i := 0; i < GetSize(s); i++ {
		if current.GetContent() > max {
			max = current.GetContent()
		}
		current = current.GetNext()
	}
	
	return max
}

// GetMinPos returns the position of the minimum value in the stack
func GetMinPos(s *Stack) int {
	if IsEmpty(s) {
		return 0
	}
	
	current := GetHead(s)
	min := math.MaxInt // Inicializujeme na velmi vysokou hodnotu
	minPos := 0
	
	// Procházíme všechny prvky včetně prvního
	for i := 0; i < GetSize(s); i++ {
		if current.GetContent() < min {
			min = current.GetContent()
			minPos = i
		}
		current = current.GetNext()
	}
	
	return minPos
}

// GetMaxPos returns the position of the maximum value in the stack
func GetMaxPos(s *Stack) int {
	if IsEmpty(s) {
		return 0
	}
	
	current := GetHead(s)
	max := current.GetContent()
	maxPos := 0
	
	for i := 0; i < GetSize(s); i++ {
		if current.GetContent() > max {
			max = current.GetContent()
			maxPos = i
		}
		current = current.GetNext()
	}
	
	return maxPos
}

// getNodeIndex returns the index of a node in its stack
func GetNodeIndex(node *Node, s *Stack) int {
	if s == nil || node == nil {
		return -1
	}
	
	index := 0
	current := GetHead(s)
	
	for current != nil {
		if current == node {
			return index
		}
		current = current.GetNext()
		index++
	}
	
	return -1
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


// getNodeIndexByValue returns the index of a node with specific value in the stack
func GetNodeIndexByValue(s *Stack, value int) int {
	if s == nil {
		return -1
	}
	
	index := 0
	current := GetHead(s)
	
	for current != nil {
		if current.GetContent() == value {
			return index
		}
		current = current.GetNext()
		index++
	}
	
	return -1
}