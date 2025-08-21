package stack

import (
	"fmt"
	"testing"
)

func TestDebugPushFromFixed(t *testing.T) {
	// Create source stack using FromSlice (like C implementation)
	source := FromSlice([]int{1, 2, 3})
	dest := New()
	
	fmt.Printf("Source after pushing: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	
	// Create destination with sufficient capacity (like C implementation)
	dest = &Stack{
		stack:  make([]int, 3), // Allocate space for 3 elements
		size:   3,              // Set capacity to 3
		top:    0,              // Start empty
		bottom: 0,              // Start empty
	}
	
	fmt.Printf("Dest after FromSlice: %v (size: %d, top: %d, bottom: %d)\n", 
		dest.ToSlice(), dest.size, dest.top, dest.bottom)
	
	// Push first element from source to dest
	if !dest.PushFrom(source) {
		t.Error("First PushFrom should succeed")
	}
	
	fmt.Printf("After first PushFrom:\n")
	fmt.Printf("  Source: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	fmt.Printf("  Dest: %v (size: %d, top: %d, bottom: %d)\n", 
		dest.ToSlice(), dest.size, dest.top, dest.bottom)
	
	// Push second element from source to dest
	if !dest.PushFrom(source) {
		t.Error("Second PushFrom should succeed")
	}
	
	fmt.Printf("After second PushFrom:\n")
	fmt.Printf("  Source: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	fmt.Printf("  Dest: %v (size: %d, top: %d, bottom: %d)\n", 
		dest.ToSlice(), dest.size, dest.top, dest.bottom)
	
	// Push third element from source to dest
	if !dest.PushFrom(source) {
		t.Error("Third PushFrom should succeed")
	}
	
	fmt.Printf("After third PushFrom:\n")
	fmt.Printf("  Source: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	fmt.Printf("  Dest: %v (size: %d, top: %d, bottom: %d)\n", 
		dest.ToSlice(), dest.size, dest.top, dest.bottom)
}
