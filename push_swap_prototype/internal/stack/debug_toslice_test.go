package stack

import (
	"fmt"
	"testing"
)

func TestDebugToSlice(t *testing.T) {
	// Create a stack with the state from the debug output
	s := New()
	s.stack = []int{0, 2, 3, 0} // size 4, top 1, bottom 3
	s.size = 4
	s.top = 1
	s.bottom = 3
	
	fmt.Printf("Stack: %v, size: %d, top: %d, bottom: %d\n", s.stack, s.size, s.top, s.bottom)
	fmt.Printf("CurrentSize: %d\n", s.CurrentSize())
	fmt.Printf("ToSlice: %v\n", s.ToSlice())
	
	// Debug the ToSlice traversal
	fmt.Printf("Traversal:\n")
	index := s.top
	for i := 0; i < s.CurrentSize(); i++ {
		fmt.Printf("  Index %d: value %d\n", index, s.stack[index])
		index = s.NextDown(index)
	}
	
	// Check individual positions
	fmt.Printf("GetValueAtPosition0(0): %d\n", s.GetValueAtPosition0(0))
	fmt.Printf("GetValueAtPosition0(1): %d\n", s.GetValueAtPosition0(1))
	fmt.Printf("GetValueAtPosition0(2): %d\n", s.GetValueAtPosition0(2))
}
