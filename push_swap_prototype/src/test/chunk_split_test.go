package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestChunkSplitFullChunk tests the chunk_split function with full 100-element chunk
// Log reference: Line 138 - "Chunk split completed: MIN chunk: loc=3, size=34, MID chunk: loc=2, size=33, MAX chunk: loc=1, size=33"
func TestChunkSplitFullChunk(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}
	
	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)
	
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 100, // EXACT from log line 28
	}
	
	dest := &stack.SplitDest{}
	
	// Act
	solver.ChunkSplit(ps, chunk, dest)
	
	// Assert - EXACT results from log line 138
	if dest.Min.Size != 34 {
		t.Errorf("Min chunk size = %d, want 34 (from log line 138)", dest.Min.Size)
	}
	if dest.Mid.Size != 33 {
		t.Errorf("Mid chunk size = %d, want 33 (from log line 138)", dest.Mid.Size)
	}
	if dest.Max.Size != 33 {
		t.Errorf("Max chunk size = %d, want 33 (from log line 138)", dest.Max.Size)
	}
	
	// Check that sizes sum to original chunk size
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 100 {
		t.Errorf("Total split size = %d, want 100 (from log line 28)", totalSize)
	}
	
	// Check locations from log line 138
	if dest.Min.Loc != stack.BOTTOM_B {
		t.Errorf("Min chunk location = %v, want BOTTOM_B (from log line 138)", dest.Min.Loc)
	}
	if dest.Mid.Loc != stack.TOP_B {
		t.Errorf("Mid chunk location = %v, want TOP_B (from log line 138)", dest.Mid.Loc)
	}
	if dest.Max.Loc != stack.BOTTOM_A {
		t.Errorf("Max chunk location = %v, want BOTTOM_A (from log line 138)", dest.Max.Loc)
	}
}
