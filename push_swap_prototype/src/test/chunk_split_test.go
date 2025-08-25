package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestChunkSplitFullChunk tests the chunk_split function with full 100-element chunk
// Log reference: Line 155-173 (entry) and Line 16264-16276 (exit) - chunk_split with 100 elements
func TestChunkSplitFullChunk(t *testing.T) {
	// Arrange - EXACT data from log line 155-173 (function entry)
	inputArray := []int{6, 76, 34, 35, 94, 78, 89, 67, 83, 65, 93, 39, 2, 91, 12, 37, 14, 9, 22, 42, 70, 61, 25, 74, 19, 48, 23, 11, 79, 29, 81, 16, 5, 49, 52, 97, 59, 57, 36, 33, 88, 10, 73, 66, 27, 8, 40, 68, 55, 46, 26, 21, 20, 45, 69, 85, 63, 87, 7, 77, 100, 56, 95, 41, 62, 54, 31, 17, 72, 4, 90, 1, 15, 30, 82, 92, 24, 60, 44, 43, 13, 98, 50, 99, 96, 28, 38, 3, 64, 53, 58, 51, 32, 84, 47, 75, 71, 86, 80, 18}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A, // EXACT from log line 155 - "Splitting chunk: loc=0, size=100"
		Size: 100, // EXACT from log line 155
	}

	// Act
	dest := solver.ChunkSplit(ps, chunk)

	// Assert - EXACT results from log line 16264-16276 (function exit)
	// Stack A final size=33, Stack B final size=67 (from log line 16264)
	// This means MAX chunk (stays in A) = 33, MIN+MID chunks (moved to B) = 67
	expectedMaxSize := 33 // Elements that stay in Stack A (from log)
	expectedMinMidSize := 67 // Elements moved to Stack B (from log)
	
	// Check that MAX chunk size matches Stack A final size from log
	if dest.Max.Size != expectedMaxSize {
		t.Errorf("Max chunk size = %d, want %d (from log line 16264 - Stack A size=33)", dest.Max.Size, expectedMaxSize)
	}
	
	// Check that MIN + MID chunks sum to elements moved to Stack B from log
	totalMovedSize := dest.Min.Size + dest.Mid.Size
	if totalMovedSize != expectedMinMidSize {
		t.Errorf("Total moved chunks size = %d, want %d (from log line 16264 - Stack B size=67)", totalMovedSize, expectedMinMidSize)
	}

	// Check that sizes sum to original chunk size
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 100 {
		t.Errorf("Total split size = %d, want 100 (from log line 155)", totalSize)
	}

	// Check locations - EXACT from implementation setSplitLoc() for TOP_A
	// MIN chunk goes to BOTTOM_B (location 3), MID chunk goes to TOP_B (location 2), MAX chunk goes to BOTTOM_A (location 1)
	if dest.Max.Loc != stack.BOTTOM_A {
		t.Errorf("Max chunk location = %v, want BOTTOM_A (from implementation setSplitLoc for TOP_A)", dest.Max.Loc)
	}
	if dest.Min.Loc != stack.BOTTOM_B {
		t.Errorf("Min chunk location = %v, want BOTTOM_B (from implementation setSplitLoc for TOP_A)", dest.Min.Loc)
	}
	if dest.Mid.Loc != stack.TOP_B {
		t.Errorf("Mid chunk location = %v, want TOP_B (from implementation setSplitLoc for TOP_A)", dest.Mid.Loc)
	}

	// Verify that sizes sum to original chunk size
	totalSize = dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 100 {
		t.Errorf("Total split size = %d, want 100 (from original chunk size)", totalSize)
	}

	// Verify final stack states from log line 16264-16276 (function exit)
	// Stack A should contain the MAX chunk elements: [76 94 78 89 83 93 91 70 74 79 81 97 88 73 68 69 85 87 77 100 95 72 90 82 92 98 99 96 84 75 71 86 80]
	expectedStackA := []int{76, 94, 78, 89, 83, 93, 91, 70, 74, 79, 81, 97, 88, 73, 68, 69, 85, 87, 77, 100, 95, 72, 90, 82, 92, 98, 99, 96, 84, 75, 71, 86, 80}
	actualStackA := ps.A.ToSlice()
	
	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Final Stack A size = %d, want %d (from log line 16264)", len(actualStackA), len(expectedStackA))
	}
	
	// Check first 33 elements of Stack A (the ones we care about)
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 16264)", i, actualStackA[i], expectedStackA[i])
		}
	}
}
