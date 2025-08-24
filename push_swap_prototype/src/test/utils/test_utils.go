package utils

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// StringToLoc converts a string representation of location to the corresponding Loc constant
func StringToLoc(locStr string) stack.Loc {
	switch locStr {
	case "TOP_A":
		return stack.TOP_A
	case "BOTTOM_A":
		return stack.BOTTOM_A
	case "TOP_B":
		return stack.TOP_B
	case "BOTTOM_B":
		return stack.BOTTOM_B
	default:
		return -1 // Invalid location
	}
}

// CreateChunk creates a chunk with the specified location and size
func CreateChunk(chunkLocStr string, chunkSize int) (*stack.Chunk, error) {
	chunkLoc := StringToLoc(chunkLocStr)
	if chunkLoc == -1 {
		return nil, fmt.Errorf("invalid chunk location: %s", chunkLocStr)
	}
	
	return &stack.Chunk{
		Loc:  chunkLoc,
		Size: chunkSize,
	}, nil
}

// CreatePushSwapData creates and initializes PushSwapData with the appropriate stack
func CreatePushSwapData(inputArray []int, chunkLoc stack.Loc) *stack.PushSwapData {
	ps := stack.NewPushSwapDataWithCapacity(len(inputArray))
	
	// Initialize the correct stack based on chunk location
	switch chunkLoc {
	case stack.TOP_A, stack.BOTTOM_A:
		// For stack A tests, initialize stack A
		stack.InitializeFromSlice(ps, inputArray)
	case stack.TOP_B, stack.BOTTOM_B:
		// For stack B tests, initialize stack B
		ps.B = stack.FromSlice(inputArray)
	}
	
	return ps
}
