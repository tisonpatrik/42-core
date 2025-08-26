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
        stack.stack[stack.Top] = value
        stack.Bottom = stack.Top
    } else {
        // Move top up and place value
        stack.Top = NextUp(stack, stack.Top)
        stack.stack[stack.Top] = value
    }
}

func Peek(stack *Stack) *int {
	if GettSize(stack) == 0 {
		return nil
	}
	return &stack.stack[stack.Top]
}

func Pop(stack *Stack) int {
	if GettSize(stack) == 0 {
		return nullValue
	}
	value := stack.stack[stack.Top]
	stack.stack[stack.Top] = nullValue
	stack.Top = NextDown(stack, stack.Top)
	return value
}

// NextUp = next_up (C)
func NextUp(s *Stack,index int) int {
	// stejné chování jako C: na prázdném stacku se index nemění
	if GettSize(s) == 0 {
		return index
	}
	if index == 0 {
		return s.capacity - 1
	}
	return index - 1
}

// NextDown = next_down (C)
func NextDown(s *Stack,index int) int {
	if GettSize(s) == 0 {
		return index
	}
	if index == s.capacity-1 {
		return 0
	}
	return index + 1
}

// GetValue = value (C) – 1-based pozice
