package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// chunkToTheTop moves the chunk to the top of its stack
func chunkToTheTop(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("=== CHUNK_TO_THE_TOP ===\n")
	fmt.Printf("Before: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	fmt.Printf("Stack A size: %d, Stack B size: %d\n", ps.A.Size(), ps.B.Size())
	
	// Exactly like C implementation - just update location, don't move elements
	if chunk.Loc == stack.BOTTOM_B && ps.B.CurrentSize() == chunk.Size {
		fmt.Printf("Moving BOTTOM_B -> TOP_B (B size == chunk size)\n")
		chunk.Loc = stack.TOP_B
	}
	if chunk.Loc == stack.BOTTOM_A && ps.A.CurrentSize() == chunk.Size {
		fmt.Printf("Moving BOTTOM_A -> TOP_A (A size == chunk size)\n")
		chunk.Loc = stack.TOP_A
	}
	
	fmt.Printf("After: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	fmt.Printf("=== CHUNK_TO_THE_TOP END ===\n")
}
