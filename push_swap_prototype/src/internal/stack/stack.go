package stack

const nullValue = -1

type Stack struct {
	Stack  []int
	capacity   int
	Top    int 
	Bottom int
}

func InitStack(size int) *Stack {
	stack := &Stack{
		Stack:  make([]int, size),
		capacity:   size,
		Top:    0,
		Bottom: 0,
	}
	
	for i := range stack.Stack {
		stack.Stack[i] = nullValue
	}
	
	return stack
}


func Push(stack *Stack, value int) {
    if IsFull(stack) {
        panic("Stack is full")
    }
    
    if value <= nullValue {
        panic("Cannot push negative numbers or null values")
    }
    
    stack.Stack[stack.Top] = value
    stack.Bottom = NextDown(stack, stack.Bottom)
}

func Peek(stack *Stack) *int {
	if GettSize(stack) == 0 {
		return nil
	}
	return &stack.Stack[stack.Top]
}


func GettSize(s *Stack) int {
	if s.capacity == 0 || (s.Top == s.Bottom && s.Stack[s.Top] == 0) {
		return 0
	}
	
	if s.Top > s.Bottom {
		return (s.capacity - s.Top) + (s.Bottom + 1)
	} else {
		return s.Bottom - s.Top + 1
	}
}

func IsSorted(stack *Stack) bool {
	i := stack.Top
	rank := 1

	for rank <= stack.capacity {
		if stack.Stack[i] != rank {
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
	s.Stack = values
	s.Bottom = s.capacity - 1
}

func Value(s *Stack, pos int) int {
	if GettSize(s) == 0 || pos <= 0 {
		return 0
	}
	i := s.Top
	for j := 1; j < pos; j++ {
		i = NextDown(s,i)
	}
	return s.Stack[i]
}