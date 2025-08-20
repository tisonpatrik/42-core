package stack

type (
	Stack struct {
		top *node
		length int
	}
	node struct {
		value any
		prev *node
	}	
)

// Create a new stack
func New() *Stack {
	return &Stack{nil,0}
}

// Return the number of items in the stack
func (this *Stack) Len() int {
	return this.length
}

// IsEmpty returns true if the stack is empty
func (s *Stack) IsEmpty() bool {
	return s.length == 0
}

// Size returns the number of elements in the stack
func (s *Stack) Size() int {
	return s.length
}

// View the top item on the stack
func (this *Stack) Peek() any {
	if this.length == 0 {
		return nil
	}
	return this.top.value
}

// Pop the top item of the stack and return it
func (this *Stack) Pop() any {
	if this.length == 0 {
		return nil
	}
	
	n := this.top
	this.top = n.prev
	this.length--
	return n.value
}

// Push a value onto the top of the stack
func (this *Stack) Push(value any) {
	n := &node{value,this.top}
	this.top = n
	this.length++
}

// ToSlice returns a slice representation of the stack (top to bottom)
func (s *Stack) ToSlice() []int {
	result := make([]int, 0, s.length)
	current := s.top
	for current != nil {
		if val, ok := current.value.(int); ok {
			result = append(result, val)
		}
		current = current.prev
	}
	return result
}

// FromSlice creates a stack from a slice (first element becomes top)
func FromSlice(values []int) *Stack {
	s := New()
	// Push in reverse order so first element becomes top
	for i := len(values) - 1; i >= 0; i-- {
		s.Push(values[i])
	}
	return s
}