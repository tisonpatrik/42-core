package stack

// NextUp = next_up (C)
func NextUp(s *Stack,index int) int {
	// stejné chování jako C: na prázdném stacku se index nemění
	if CurrentSize(s) == 0 {
		return index
	}
	if index == 0 {
		return s.Size - 1
	}
	return index - 1
}

// NextDown = next_down (C)
func NextDown(s *Stack,index int) int {
	if CurrentSize(s) == 0 {
		return index
	}
	if index == s.Size-1 {
		return 0
	}
	return index + 1
}

// GetValue = value (C) – 1-based pozice
func Value(s *Stack, pos int) int {
	if CurrentSize(s) == 0 || pos <= 0 {
		return 0
	}
	i := s.Top
	for j := 1; j < pos; j++ {
		i = NextDown(s,i)
	}
	return s.Stack[i]
}

// CurrentSize = current_size (C)
func CurrentSize(s *Stack) int {
	if s.Top == s.Bottom && s.Stack[s.Top] == 0 {
		return 0
	}
	if s.Top > s.Bottom {
		return (s.Size - s.Top) + (s.Bottom + 1)
	}
	return s.Bottom - s.Top + 1
}

// IsFull = is_full (C)
func IsFull(s *Stack) bool {
	return CurrentSize(s) == s.Size
}


