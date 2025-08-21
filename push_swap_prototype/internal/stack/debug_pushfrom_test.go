package stack

import (
	"fmt"
	"testing"
)

func TestDebugPushFrom(t *testing.T) {
	// Create source stack using FromSlice (like C implementation)
	source := FromSlice([]int{1, 2, 3})
	dest := New()
	
	fmt.Printf("Source after pushing: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	
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
