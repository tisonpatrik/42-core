package stack

import (
	"fmt"
	"testing"
)

func TestDebugPushFromStep(t *testing.T) {
	source := New()
	dest := New()
	
	// Push one element to source
	source.Push(5)
	
	fmt.Printf("Source: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	
	// Create destination with capacity
	dest = FromSlice([]int{0, 0})
	
	fmt.Printf("Dest before: %v (size: %d, top: %d, bottom: %d)\n", 
		dest.ToSlice(), dest.size, dest.top, dest.bottom)
	
	// Debug the PushFrom operation step by step
	fmt.Printf("Source top value: %d\n", source.stack[source.top])
	fmt.Printf("Dest top before: %d\n", dest.top)
	fmt.Printf("NextUp(dest.top): %d\n", dest.NextUp(dest.top))
	
	// Try to push
	result := dest.PushFrom(source)
	fmt.Printf("PushFrom result: %t\n", result)
	
	fmt.Printf("Dest after: %v (size: %d, top: %d, bottom: %d)\n", 
		dest.ToSlice(), dest.size, dest.top, dest.bottom)
	fmt.Printf("Source after: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
}
