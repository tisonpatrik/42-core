package stack

const nullValue = -1

type Stack struct {
	stack  []int
	capacity   int
	Top    int 
	Bottom int
}

func InitStack(size int) *Stack {
	stack := &Stack{
		stack:  make([]int, size),
		capacity:   size,
		Top:    0,
		Bottom: 0,
	}
	
	for i := range stack.stack {
		stack.stack[i] = nullValue
	}
	
	return stack
}

func GettSize(s *Stack) int {
	count := 0
	for _, val := range s.stack {
		if val != nullValue {
			count++
		}
	}
	return count
}

func IsSorted(stack *Stack) bool {
	i := stack.Top
	rank := 1

	for rank <= stack.capacity {
		if stack.stack[i] != rank {
			return false
		}
		rank++
		i = NextDown(stack, i)
	}
	return true
}


func IsFull(s *Stack) bool {
	return GettSize(s) == s.capacity
}

func FillStack(s *Stack, values []int) {
	// Validate input
	if s == nil {
		panic("Stack is nil")
	}
	if len(values) != s.capacity {
		panic("Cannot fill stack: values exceed capacity")
	}
	// Push each value individually using the stack's push mechanism
	for _, val := range values {
		// Validate before each push
		if IsFull(s) {
			panic("Stack became full unexpectedly during fill operation")
		}
		
		// Validate value
		if val <= nullValue {
			panic("Cannot push negative numbers or null values")
		}
		
		// Push to stack (this will handle all the index management)
		Push(s, val)
	}
}

func GetValue(s *Stack, pos int) int {
	if pos < 0 || pos >= len(s.stack) {
		return nullValue
	}
	return s.stack[pos]
}