package stack

import (
	"fmt"
	"testing"
)

func TestDebugCurrentSize(t *testing.T) {
	// Create a stack with [2, 3] where top = 1, bottom = 0
	s := New()
	s.stack = []int{3, 2} // [bottom, top] = [0, 1]
	s.size = 2
	s.top = 1
	s.bottom = 0
	
	fmt.Printf("Stack: %v, size: %d, top: %d, bottom: %d\n", s.stack, s.size, s.top, s.bottom)
	fmt.Printf("CurrentSize: %d\n", s.CurrentSize())
	fmt.Printf("ToSlice: %v\n", s.ToSlice())
	
	// Check the condition that's failing
	fmt.Printf("top == bottom: %t\n", s.top == s.bottom)
	fmt.Printf("stack[top] == 0: %t\n", s.stack[s.top] == 0)
	fmt.Printf("top > bottom: %t\n", s.top > s.bottom)
	
	if s.top > s.bottom {
		calc := (s.size - s.top) + (s.bottom + 1)
		fmt.Printf("Calculated size: (%d - %d) + (%d + 1) = %d\n", s.size, s.top, s.bottom, calc)
	} else {
		calc := s.bottom - s.top + 1
		fmt.Printf("Calculated size: %d - %d + 1 = %d\n", s.bottom, s.top, calc)
	}
}
