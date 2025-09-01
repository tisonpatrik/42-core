package stack

import "math"

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


func Pop(s *Stack) *Node {
	if s.size == 0 {
		return nil
	}

	node := s.head
	
	if s.size == 1 {
		s.head = nil
		s.tail = nil
	} else {
		s.head = s.head.next
		s.head.prev = nil
	}
	
	s.size--
	return node
}

func Rotate(s *Stack) bool {
	if s.size <= 1 {
		return false
	}
	
	topNode := s.head
	
	s.head = s.head.next
	s.head.prev = nil
	
	topNode.next = nil
	topNode.prev = s.tail
	s.tail.next = topNode
	s.tail = topNode
	
	return true
}

func ReverseRotate(s *Stack) bool {
	if s.size <= 1 {
		return false
	}
	
	bottomNode := s.tail
	
	s.tail = s.tail.prev
	s.tail.next = nil
	
	bottomNode.prev = nil
	bottomNode.next = s.head
	s.head.prev = bottomNode
	s.head = bottomNode
	
	return true
}


func Swap(s *Stack) bool {
	if s.size < 2 {
		return false
	}
	
	s.head.content, s.head.next.content = s.head.next.content, s.head.content
	return true
}


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

func FillStack(s *Stack, values []int) {
	if s == nil {
		panic("Stack is nil")
	}
	
	ClearStack(s)
	
	for i := len(values) - 1; i >= 0; i-- {
		if values[i] < 0 {
			panic("Cannot push negative numbers")
		}
		Push(s, values[i])
	}
}

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

func GetMinPos(s *Stack) int {
	if IsEmpty(s) {
		return 0
	}
	
	current := GetHead(s)
	min := math.MaxInt
	minPos := 0
	
	for i := 0; i < GetSize(s); i++ {
		if current.GetContent() < min {
			min = current.GetContent()
			minPos = i
		}
		current = current.GetNext()
	}
	
	return minPos
}

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