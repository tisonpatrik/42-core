package stack

import (
	"fmt"
	"testing"
)

func TestDebugCurrentSizeFixed(t *testing.T) {
	// Create a stack with the state from the debug output
	s := New()
	s.stack = []int{3, 2, 1} // size 3, top 2, bottom 0
	s.size = 3
	s.top = 2
	s.bottom = 0
	
	fmt.Printf("Stack: %v, size: %d, top: %d, bottom: %d\n", s.stack, s.size, s.top, s.bottom)
	fmt.Printf("CurrentSize: %d\n", s.CurrentSize())
	fmt.Printf("ToSlice: %v\n", s.ToSlice())
	
	// Debug the CurrentSize calculation
	fmt.Printf("top > bottom: %t\n", s.top > s.bottom)
	if s.top > s.bottom {
		calc := (s.size - s.top) + (s.bottom + 1)
		fmt.Printf("Calculated size: (%d - %d) + (%d + 1) = %d\n", s.size, s.top, s.bottom, calc)
	} else {
		calc := s.bottom - s.top + 1
		fmt.Printf("Calculated size: %d - %d + 1 = %d\n", s.bottom, s.top, calc)
	}
	
	// Debug the ToSlice traversal
	fmt.Printf("ToSlice traversal:\n")
	index := s.top
	for i := 0; i < s.CurrentSize(); i++ {
		fmt.Printf("  Index %d: value %d\n", index, s.stack[index])
		index = s.NextDown(index)
	}
}
