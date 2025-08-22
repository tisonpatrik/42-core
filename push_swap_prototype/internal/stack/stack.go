package stack

// Stack represents a circular buffer stack like the C implementation
type Stack struct {
	stack  []int
	size   int  // capacity of the buffer
	top    int  // index of top element
	bottom int  // index of bottom element
}

// New creates a new empty stack
func New() *Stack {
	return &Stack{
		stack:  []int{},
		size:   0,
		top:    0,
		bottom: 0,
	}
}

// InitWithCapacity initializes a stack with specific capacity (like C init_stack)
func (s *Stack) InitWithCapacity(capacity int) {
	s.stack = make([]int, capacity)
	s.size = capacity
	s.top = 0
	s.bottom = 0
	// Zero out the array like C memset
	for i := range s.stack {
		s.stack[i] = 0
	}
}

// FillFromSlice fills a stack with values from a slice (like C fill_stack)
func (s *Stack) FillFromSlice(values []int) {
	if len(values) > s.size {
		return // Cannot fit more elements than capacity
	}
	
	// Copy values to stack array
	copy(s.stack, values)
	
	// Set pointers like C fill_stack
	s.top = 0
	s.bottom = len(values) - 1
}

// Size returns the current number of elements in the stack
func (s *Stack) Size() int {
	return s.CurrentSize()
}

// Peek returns the top element without removing it
func (s *Stack) Peek() int {
	if s.CurrentSize() == 0 {
		return 0
	}
	return s.stack[s.top]
}

// PeekValue returns the value of the top element
func (s *Stack) PeekValue() int {
	return s.Peek()
}

// IsEmpty returns true if the stack is empty
func (s *Stack) IsEmpty() bool {
	return s.CurrentSize() == 0
}

// Push adds a new element to the top of the stack
func (s *Stack) Push(val int) {
	if s.size == 0 {
		// Initialize with first element
		s.stack = []int{val}
		s.size = 1
		s.top = 0
		s.bottom = 0
	} else if s.IsFull() {
		// Need to expand - add element at the end
		s.stack = append(s.stack, val)
		s.size = len(s.stack)
		s.top = s.size - 1
	} else {
		// Add element by moving top pointer up
		s.top = s.NextUp(s.top)
		s.stack[s.top] = val
	}
}

// Pop removes and returns the top element
func (s *Stack) Pop() int {
	if s.CurrentSize() == 0 {
		return 0
	}
	
	val := s.stack[s.top]
	s.stack[s.top] = 0 // clear the position
	
	if s.top == s.bottom {
		// Last element - reset to empty state
		s.top = 0
		s.bottom = 0
	} else {
		// Move top pointer down
		s.top = s.NextDown(s.top)
	}
	
	return val
}

// ToSlice returns a slice representation of the stack (top to bottom)
func (s *Stack) ToSlice() []int {
	if s.CurrentSize() == 0 {
		return []int{}
	}
	
	result := make([]int, s.CurrentSize())
	index := s.top
	for i := 0; i < s.CurrentSize(); i++ {
		result[i] = s.stack[index]
		index = s.NextDown(index)
	}
	return result
}

// FromSlice creates a stack from a slice (exactly like C fill_stack)
func FromSlice(values []int) *Stack {
	s := New()
	if len(values) == 0 {
		return s
	}
	
	// Initialize stack with exact capacity (like C init_stack)
	// In C, both stacks get capacity equal to the number of input arguments
	s.stack = make([]int, len(values))
	s.size = len(values)
	
	// Fill the stack with values (like C fill_stack)
	copy(s.stack, values)
	
	// Set pointers: first element is at top, last element is at bottom
	s.top = 0
	s.bottom = len(values) - 1
	
	return s
}



// GetValueAtPosition0 returns the value at a specific position (0-based)
func (s *Stack) GetValueAtPosition0(pos int) int {
	if pos < 0 || pos >= s.CurrentSize() {
		return 0
	}
	
	index := s.top
	for i := 0; i < pos; i++ {
		index = s.NextDown(index)
	}
	return s.stack[index]
}

// GetTop returns the top index (like C implementation)
func (s *Stack) GetTop() int {
	return s.top
}

// GetBottom returns the bottom index (like C implementation)
func (s *Stack) GetBottom() int {
	return s.bottom
}

// SetTop sets the top index (like C implementation - direct field access)
func (s *Stack) SetTop(top int) {
	s.top = top
}

// SetBottom sets the bottom index (like C implementation - direct field access)
func (s *Stack) SetBottom(bottom int) {
	s.bottom = bottom
}

// GetStack returns the stack array (like C implementation)
func (s *Stack) GetStack() []int {
	return s.stack
}



// Value returns the value at a specific index (like C implementation)
func (s *Stack) Value(index int) int {
	if index < 0 || index >= s.size {
		return 0
	}
	return s.stack[index]
}

// SetValue sets the value at a specific index
func (s *Stack) SetValue(index int, val int) bool {
	if index < 0 || index >= s.size {
		return false
	}
	s.stack[index] = val
	return true
}

