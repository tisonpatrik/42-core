package stack

import (
	"fmt"
	"testing"
)

func TestDebugPush(t *testing.T) {
	s := New()
	
	fmt.Printf("Initial state: size=%d, top=%d, bottom=%d, stack=%v\n", 
		s.size, s.top, s.bottom, s.stack)
	
	// Push first element
	s.Push(3)
	fmt.Printf("After Push(3): size=%d, top=%d, bottom=%d, stack=%v\n", 
		s.size, s.top, s.bottom, s.stack)
	
	// Push second element
	s.Push(2)
	fmt.Printf("After Push(2): size=%d, top=%d, bottom=%d, stack=%v\n", 
		s.size, s.top, s.bottom, s.stack)
	
	// Push third element
	s.Push(1)
	fmt.Printf("After Push(1): size=%d, top=%d, bottom=%d, stack=%v\n", 
		s.size, s.top, s.bottom, s.stack)
	
	fmt.Printf("Final ToSlice: %v\n", s.ToSlice())
	fmt.Printf("CurrentSize: %d\n", s.CurrentSize())
}
