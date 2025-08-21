package stack

import (
	"fmt"
	"testing"
)

func TestDebugStack(t *testing.T) {
	// Test FromSlice behavior
	values := []int{3, 1, 4}
	s := FromSlice(values)
	
	fmt.Printf("Stack created from %v\n", values)
	fmt.Printf("Size: %d, Top: %d, Bottom: %d\n", s.size, s.top, s.bottom)
	fmt.Printf("Stack array: %v\n", s.stack)
	fmt.Printf("CurrentSize: %d\n", s.CurrentSize())
	fmt.Printf("ToSlice: %v\n", s.ToSlice())
	
	// Test NextUp and NextDown
	fmt.Printf("NextUp(0): %d\n", s.NextUp(0))
	fmt.Printf("NextUp(1): %d\n", s.NextUp(1))
	fmt.Printf("NextUp(2): %d\n", s.NextUp(2))
	fmt.Printf("NextDown(0): %d\n", s.NextDown(0))
	fmt.Printf("NextDown(1): %d\n", s.NextDown(1))
	fmt.Printf("NextDown(2): %d\n", s.NextDown(2))
	
	// Test GetValueAtPosition
	fmt.Printf("GetValueAtPosition(1): %d\n", s.GetValueAtPosition(1))
	fmt.Printf("GetValueAtPosition(2): %d\n", s.GetValueAtPosition(2))
	fmt.Printf("GetValueAtPosition(3): %d\n", s.GetValueAtPosition(3))
	
	// Test GetValueAtPosition0
	fmt.Printf("GetValueAtPosition0(0): %d\n", s.GetValueAtPosition0(0))
	fmt.Printf("GetValueAtPosition0(1): %d\n", s.GetValueAtPosition0(1))
	fmt.Printf("GetValueAtPosition0(2): %d\n", s.GetValueAtPosition0(2))
}
