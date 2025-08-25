package stack

// NextUp = next_up (C)
func (s *Stack) NextUp(index int) int {
	// stejné chování jako C: na prázdném stacku se index nemění
	if s.CurrentSize() == 0 {
		return index
	}
	if index == 0 {
		return s.size - 1
	}
	return index - 1
}

// NextDown = next_down (C)
func (s *Stack) NextDown(index int) int {
	if s.CurrentSize() == 0 {
		return index
	}
	if index == s.size-1 {
		return 0
	}
	return index + 1
}

// GetValue = value (C) – 1-based pozice
func (s *Stack) GetValue(pos int) int {
	if s.CurrentSize() == 0 || pos <= 0 {
		return 0
	}
	i := s.top
	for j := 1; j < pos; j++ {
		i = s.NextDown(i)
	}
	return s.stack[i]
}

// CurrentSize = current_size (C)
func (s *Stack) CurrentSize() int {
	// ochrana na neinit stav
	if s.size == 0 || len(s.stack) == 0 {
		return 0
	}
	// přesná C logika prázdného stavu (sentinel)
	if s.top == s.bottom && s.stack[s.top] == 0 {
		return 0
	}
	if s.top > s.bottom {
		return (s.size - s.top) + (s.bottom + 1)
	}
	return s.bottom - s.top + 1
}

// IsFull = is_full (C)
func (s *Stack) IsFull() bool {
	return s.CurrentSize() == s.size
}


