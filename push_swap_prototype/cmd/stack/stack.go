package stack

import (
	"container/list"
)

// Stacks represents the two stacks a and b for push_swap
type Stacks struct {
	A *list.List
	B *list.List
}


// NewStacks creates and returns new empty stacks
func NewStacks() *Stacks {
	return &Stacks{
		A: list.New(),
		B: list.New(),
	}
}

// InitFromSlice initializes stack A from a slice of integers
func (s *Stacks) InitFromSlice(numbers []int) {
	s.A.Init()
	for _, num := range numbers {
		s.A.PushBack(num)
	}
}


func (s *Stacks) IsSorted() bool {
	if s.A.Len() < 2 {
		return true
	}
	
	prev := s.A.Front()
	for e := prev.Next(); e != nil; e = e.Next() {
		if prev.Value.(int) > e.Value.(int) {
			return false
		}
		prev = e
	}
	return true
}