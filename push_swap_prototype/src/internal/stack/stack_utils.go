package stack


func Push(s *Stack, value int) {
	if IsFull(s) {
		panic("Stack is full")
	}
	if value <= nullValue {
		panic("Cannot push negative numbers or null values")
	}

	// stack is empty
	if GetSize(s) == 0 {
		s.top = 0
		s.bottom = 0
		s.stack[s.top] = value
		return
	}

	// otherwise move top
	s.top = Previous(s, s.top)
	s.stack[s.top] = value
}


func Peek(stack *Stack) *int {
	if GetSize(stack) == 0 {
		return nil
	}
	return &stack.stack[stack.top]
}

func Pop(s *Stack) int {
	if GetSize(s) == 0 {
		return nullValue
	}

	value := s.stack[s.top]
	s.stack[s.top] = nullValue

	if s.top == s.bottom {
		// last element -> empty stack
		s.top = nullValue
		s.bottom = nullValue
		return value
	}

	// otherwise move top towards bottom (circular)
	s.top = Next(s, s.top)
	return value
}


func Previous(s *Stack, i int) int {
	if i == 0 {
		return s.capacity - 1
	}
	return i - 1
}

func Next(s *Stack, i int) int {
	if i == s.capacity-1 {
		return 0
	}
	return i + 1
}

func FillStack(s *Stack, values []int) {
    if s == nil {
        panic("Stack is nil")
    }
    if len(values) != s.capacity {
        panic("Cannot fill stack: values exceed capacity")
    }

    // Clear the buffer
    for i := range s.stack {
        s.stack[i] = nullValue
    }
	// Empty state must be -1 / -1, otherwise GetSize != 0
    s.top = nullValue
    s.bottom = nullValue

    // Now we can push; Push itself panics on overflow
    for _, val := range values {
        if val <= nullValue {
            panic("Cannot push negative numbers or null values")
        }
        Push(s, val)
    }
}

func Rotate(s *Stack) bool {
    if GetSize(s) <= 1 {
        return false
    }
    // take value from old top
    v := s.stack[s.top]

    // move top and bottom circularly
    s.top = Next(s, s.top)
    s.bottom = Next(s, s.bottom)

    // new bottom is now the old top position; put it there
    s.stack[s.bottom] = v
    return true
}

func ReverseRotate(s *Stack) bool {
    if GetSize(s) <= 1 {
        return false
    }
    // take value from old bottom
    v := s.stack[s.bottom]

    // move top and bottom circularly backwards
    s.top = Previous(s, s.top)
    s.bottom = Previous(s, s.bottom)

    // new top gets the old bottom value
    s.stack[s.top] = v
    return true
}

func Swap(s *Stack) bool {
	if GetSize(s) < 2 {
		return false
	}
	i := s.top
	j := Next(s, s.top)        // physical index of the second element
	s.stack[i], s.stack[j] = s.stack[j], s.stack[i]
	return true
}

func IsSorted(stack *Stack) bool {
	if GetSize(stack) == 0 {
		return true
	}
	
	i := stack.top
	rank := 1
	count := 0

	for count < GetSize(stack) {
		if stack.stack[i] != rank {
			return false
		}
		rank++
		i = Next(stack, i)
		count++
	}
	return true
}
