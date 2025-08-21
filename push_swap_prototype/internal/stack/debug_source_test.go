package stack

import (
	"fmt"
	"testing"
)

func TestDebugSource(t *testing.T) {
	source := New()
	
	// Push elements to source
	source.Push(1)
	source.Push(2)
	source.Push(3)
	
	fmt.Printf("Source after pushing: %v (size: %d, top: %d, bottom: %d)\n", 
		source.ToSlice(), source.size, source.top, source.bottom)
	
	// Simulate first PushFrom operation
	fmt.Printf("Before first PushFrom:\n")
	fmt.Printf("  Source top: %d, bottom: %d\n", source.top, source.bottom)
	fmt.Printf("  Source stack: %v\n", source.stack)
	
	// Simulate the PushFrom operation on source
	source.stack[source.top] = 0
	source.top = source.NextDown(source.top)
	
	fmt.Printf("After first PushFrom:\n")
	fmt.Printf("  Source top: %d, bottom: %d\n", source.top, source.bottom)
	fmt.Printf("  Source stack: %v\n", source.stack)
	fmt.Printf("  CurrentSize: %d\n", source.CurrentSize())
	fmt.Printf("  ToSlice: %v\n", source.ToSlice())
	
	// Simulate second PushFrom operation
	fmt.Printf("Before second PushFrom:\n")
	fmt.Printf("  Source top: %d, bottom: %d\n", source.top, source.bottom)
	fmt.Printf("  Source stack: %v\n", source.stack)
	
	source.stack[source.top] = 0
	source.top = source.NextDown(source.top)
	
	fmt.Printf("After second PushFrom:\n")
	fmt.Printf("  Source top: %d, bottom: %d\n", source.top, source.bottom)
	fmt.Printf("  Source stack: %v\n", source.stack)
	fmt.Printf("  CurrentSize: %d\n", source.CurrentSize())
	fmt.Printf("  ToSlice: %v\n", source.ToSlice())
}
