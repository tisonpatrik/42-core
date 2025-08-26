package stack

// Stack represents a circular buffer stack like the C implementation
type Stack struct {
	Stack  []int
	capacity   int // capacity of the buffer
	Top    int // index of top element
	Bottom int // index of bottom element
}

func GetCapacity(stack *Stack) int {
	return stack.capacity
}

func Push(stack *Stack, value int) {
	if IsFull(stack) {
		panic("Stack is full")
	}
	stack.Stack[stack.Top] = value
	stack.Top = NextDown(stack, stack.Top)
}

func Pop(stack *Stack) *int {
    if GettSize(stack) == 0 {
        return nil
    }
    value := stack.Stack[stack.Top]
    stack.Top = NextUp(stack, stack.Top)
    return &value
}

func Peek(stack *Stack) *int {
	if GettSize(stack) == 0 {
		return nil
	}
	return &stack.Stack[stack.Top]
}

func InitStack(size int) *Stack {
	stack := &Stack{
		Stack:  make([]int, size),
		capacity:   size,
		Top:    0,
		Bottom: 0,
	}
	
	for i := range stack.Stack {
		stack.Stack[i] = 0
	}
	
	return stack
}

func GettSize(s *Stack) int {
	// Check if stack is empty (either no capacity or top equals bottom with no meaningful value)
	if s.capacity == 0 || (s.Top == s.Bottom && s.Stack[s.Top] == 0) {
		return 0
	}
	
	// Calculate size based on circular buffer logic
	if s.Top > s.Bottom {
		return (s.capacity - s.Top) + (s.Bottom + 1)
	} else {
		return s.Bottom - s.Top + 1
	}
}


func IsSorted(stack *Stack) bool {
	i := stack.Top
	rank := 1

	for rank <= GetCapacity(stack) {
		if stack.Stack[i] != rank {
			return false
		}
		rank++
		i = NextDown(stack, i)
	}
	return true
}


func IsFull(s *Stack) bool {
	return GettSize(s) == GetCapacity(s)
}
