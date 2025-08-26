package stack


func Push(stack *Stack, value int) {
    if IsFull(stack) {
        panic("Stack is full")
    }
    
    if value <= nullValue {
        panic("Cannot push negative numbers or null values")
    }
    
    // If stack is empty, set both top and bottom to same position
    if GettSize(stack) == 0 {
        stack.top = 0
        stack.bottom = 0
        stack.stack[stack.top] = value
    } else {
        // Move top up and place value
        stack.top = Previous(stack, stack.top)
        stack.stack[stack.top] = value
    }
}

func Peek(stack *Stack) *int {
	if GettSize(stack) == 0 {
		return nil
	}
	return &stack.stack[stack.top]
}

func Pop(stack *Stack) int {
	if GettSize(stack) == 0 {
		return nullValue
	}
	
	value := stack.stack[stack.top]
	stack.stack[stack.top] = nullValue
	
	// If this was the last element, mark stack as empty
	if stack.top == stack.bottom {
		stack.bottom = -1
		// Don't change top - keep it at 0 for empty stack
	} else {
		// Move top down
		stack.top = Next(stack, stack.top)
	}
	
	return value
}

// Previous = next_up (C)
func Previous(s *Stack, index int) int {
	if index == 0 {
		return s.capacity - 1
	}
	return index - 1
}

// Next = next_down (C)
func Next(s *Stack, index int) int {
	if index == s.capacity-1 {
		return 0
	}
	return index + 1
}



func FillStack(s *Stack, values []int) {
	// Validate input
	if s == nil {
		panic("Stack is nil")
	}
	if len(values) != s.capacity {
		panic("Cannot fill stack: values exceed capacity")
	}
	
	// Clear the stack first
	for i := range s.stack {
		s.stack[i] = nullValue
	}
	s.top = 0
	s.bottom = -1 // Mark as empty
	
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


func SetTop(s *Stack, newTop int) {
	s.top = newTop
}

// SetBottom sets the bottom index directly  
func SetBottom(s *Stack, newBottom int) {
	s.bottom = newBottom
}

func IsSorted(stack *Stack) bool {
	if GettSize(stack) == 0 {
		return true
	}
	
	i := stack.top
	rank := 1
	count := 0

	for count < GettSize(stack) {
		if stack.stack[i] != rank {
			return false
		}
		rank++
		i = Next(stack, i)
		count++
	}
	return true
}
