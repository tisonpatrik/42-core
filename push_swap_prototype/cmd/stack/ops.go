package stack

// sa (swap a): Swap the first 2 elements at the top of stack a
func (s *Stacks) Sa() {
	if s.A.Len() < 2 {
		return
	}
	
	first := s.A.Front()
	second := first.Next()
	
	// Swap values
	first.Value, second.Value = second.Value, first.Value
}

// sb (swap b): Swap the first 2 elements at the top of stack b
func (s *Stacks) Sb() {
	if s.B.Len() < 2 {
		return
	}
	
	first := s.B.Front()
	second := first.Next()
	
	// Swap values
	first.Value, second.Value = second.Value, first.Value
}

// ss: sa and sb at the same time
func (s *Stacks) Ss() {
	s.Sa()
	s.Sb()
}

// pa (push a): Take the first element at the top of b and put it at the top of a
func (s *Stacks) Pa() {
	if s.B.Len() == 0 {
		return
	}
	
	// Remove from front of B
	element := s.B.Front()
	value := s.B.Remove(element)
	
	// Add to front of A
	s.A.PushFront(value)
}

// pb (push b): Take the first element at the top of a and put it at the top of b
func (s *Stacks) Pb() {
	if s.A.Len() == 0 {
		return
	}
	
	// Remove from front of A
	element := s.A.Front()
	value := s.A.Remove(element)
	
	// Add to front of B
	s.B.PushFront(value)
}

// ra (rotate a): Shift up all elements of stack a by 1
func (s *Stacks) Ra() {
	if s.A.Len() < 2 {
		return
	}
	
	// Remove from front and add to back
	element := s.A.Front()
	value := s.A.Remove(element)
	s.A.PushBack(value)
}

// rb (rotate b): Shift up all elements of stack b by 1
func (s *Stacks) Rb() {
	if s.B.Len() < 2 {
		return
	}
	
	// Remove from front and add to back
	element := s.B.Front()
	value := s.B.Remove(element)
	s.B.PushBack(value)
}

// rr: ra and rb at the same time
func (s *Stacks) Rr() {
	s.Ra()
	s.Rb()
}

// rra (reverse rotate a): Shift down all elements of stack a by 1
func (s *Stacks) Rra() {
	if s.A.Len() < 2 {
		return
	}
	
	// Remove from back and add to front
	element := s.A.Back()
	value := s.A.Remove(element)
	s.A.PushFront(value)
}

// rrb (reverse rotate b): Shift down all elements of stack b by 1
func (s *Stacks) Rrb() {
	if s.B.Len() < 2 {
		return
	}
	
	// Remove from back and add to front
	element := s.B.Back()
	value := s.B.Remove(element)
	s.B.PushFront(value)
}

// rrr: rra and rrb at the same time
func (s *Stacks) Rrr() {
	s.Rra()
	s.Rrb()
}



