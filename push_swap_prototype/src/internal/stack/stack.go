package stack

const nullValue = -1

// circular buffer with top and bottom indices
// no negative values in the stack

type Stack struct {
	stack  []int
	capacity   int
	top    int 
	bottom int
}

func InitStack(size int) *Stack {
	stack := &Stack{
		stack:  make([]int, size),
		capacity:   size,
		top:    nullValue, 
		bottom: nullValue,
	}
	
	for i := range stack.stack {
		stack.stack[i] = nullValue
	}
	
	return stack
}

func GetSize(s *Stack) int {
	if s.top == -1 && s.bottom == -1 {
		// empty stack
		return 0
	}

	if s.top <= s.bottom {
		// top is before bottom (normal case)
		return s.bottom - s.top + 1
	}

	// wrapped case (top is "after" bottom in the circle)
	return (s.capacity - s.top) + (s.bottom + 1)
}


func IsFull(s *Stack) bool {
	return GetSize(s) == s.capacity
}

func GetTop(s *Stack) int {
	return s.top
}

func GetBottom(s *Stack) int {type Stack struct {
	stack  []int
	capacity   int
	top    int 
	bottom int
}

	return s.bottom
}

func GetValue(s *Stack, pos int) int {
	if pos < 0 || pos >= GetSize(s) {
		return nullValue
	}
	
	// Convert 0-based position to actual index
	index := (s.top + pos) % s.capacity
	return s.stack[index]
}

// NullValue returns the null value constant
func NullValue() int {
	return nullValue
}

// SetValueAt sets a value at a specific index in the stack
func SetValueAt(s *Stack, index int, value int) {
	if index >= 0 && index < s.capacity {
		s.stack[index] = value
	}
}