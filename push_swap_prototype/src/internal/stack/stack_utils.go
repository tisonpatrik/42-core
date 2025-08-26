package stack

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