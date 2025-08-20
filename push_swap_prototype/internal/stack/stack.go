package stack

// Node represents a node in the circular doubly-linked list
type Node struct {
	Val  int  // The value stored in the node
	Idx  int  // The original index in the array
	Keep bool // Whether this element should be kept in stack A (part of LIS)
	Next *Node
	Prev *Node
}

// Stack represents a circular doubly-linked list stack
type Stack struct {
	head   *Node
	length int
}

// New creates a new empty stack
func New() *Stack {
	return &Stack{nil, 0}
}

// Size returns the number of elements in the stack
func (s *Stack) Size() int {
	return s.length
}

// Peek returns the top element without removing it
func (s *Stack) Peek() *Node {
	if s.length == 0 {
		return nil
	}
	return s.head
}

// IsEmpty returns true if the stack is empty
func (s *Stack) IsEmpty() bool {
	return s.length == 0
}

// PeekValue returns the value of the top element
func (s *Stack) PeekValue() int {
	if s.length == 0 {
		return 0
	}
	return s.head.Val
}

// PeekIdx returns the index of the top element
func (s *Stack) PeekIdx() int {
	if s.length == 0 {
		return -1
	}
	return s.head.Idx
}


// Push adds a new element to the top of the stack
func (s *Stack) Push(val, idx int, keep bool) {
	node := &Node{Val: val, Idx: idx, Keep: keep}
	
	if s.length == 0 {
		node.Next = node
		node.Prev = node
		s.head = node
	} else {
		node.Next = s.head
		node.Prev = s.head.Prev
		s.head.Prev.Next = node
		s.head.Prev = node
		s.head = node
	}
	s.length++
}

// PushNode adds an existing node to the top of the stack
func (s *Stack) PushNode(node *Node) {
	// Ensure the node has clean pointers
	node.Next = nil
	node.Prev = nil
	
	if s.length == 0 {
		node.Next = node
		node.Prev = node
		s.head = node
	} else {
		node.Next = s.head
		node.Prev = s.head.Prev
		if s.head.Prev != nil {
			s.head.Prev.Next = node
		}
		s.head.Prev = node
		s.head = node
	}
	s.length++
}

// ToSlice returns a slice representation of the stack (top to bottom)
func (s *Stack) ToSlice() []int {
	if s.length == 0 {
		return []int{}
	}
	
	result := make([]int, s.length)
	current := s.head
	for i := 0; i < s.length; i++ {
		result[i] = current.Val
		current = current.Next
	}
	return result
}

// ToNodeSlice returns a slice of nodes (top to bottom)
func (s *Stack) ToNodeSlice() []*Node {
	if s.length == 0 {
		return []*Node{}
	}
	
	result := make([]*Node, s.length)
	current := s.head
	for i := 0; i < s.length; i++ {
		result[i] = current
		current = current.Next
	}
	return result
}

// FromSlice creates a stack from a slice (first element becomes top)
func FromSlice(values []int) *Stack {
	s := New()
	// Push in reverse order so first element becomes top
	for i := len(values) - 1; i >= 0; i-- {
		s.Push(values[i], i, false) // Keep will be set later by LIS algorithm
	}
	return s
}

