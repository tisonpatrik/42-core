package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
	"time"
)

// TestChunkSplitInfiniteLoop tests the infinite loop bug in chunk_split
// Log reference: Line 320-329 - Splitting chunk: loc=0, size=33 with Stack A [68 72 98 89 79 91 76 88 93 71 74 90 85 97 70 80 75 96 86 99 95 100 83 69 77 78 92 73 81 94 87 84 82]
func TestChunkSplitInfiniteLoop(t *testing.T) {
	// Arrange - EXACT data from log line 320-329
	// Stack A elements from log: [68 72 98 89 79 91 76 88 93 71 74 90 85 97 70 80 75 96 86 99 95 100 83 69 77 78 92 73 81 94 87 84 82]
	stackAData := []int{68, 72, 98, 89, 79, 91, 76, 88, 93, 71, 74, 90, 85, 97, 70, 80, 75, 96, 86, 99, 95, 100, 83, 69, 77, 78, 92, 73, 81, 94, 87, 84, 82}

	// Stack B elements from log: [65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14]
	stackBData := []int{65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state from log - chunk size 33, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 33, // EXACT from log - chunk size 33
	}

	dest := &stack.SplitDest{}

	// Act - This should cause infinite loop due to race condition
	// We'll use a timeout to detect the infinite loop
	done := make(chan bool, 1)
	
	go func() {
		solver.ChunkSplit(ps, chunk, dest)
		done <- true
	}()

	// Wait for completion or timeout
	select {
	case <-done:
		t.Log("ChunkSplit completed successfully (no infinite loop detected)")
	case <-time.After(5 * time.Second):
		t.Fatal("ChunkSplit timed out - INFINITE LOOP DETECTED! This confirms the bug.")
	}

	// If we get here, check the results
	t.Logf("Final chunk sizes: MIN=%d, MID=%d, MAX=%d", dest.Min.Size, dest.Mid.Size, dest.Max.Size)
}

// TestChunkSplitRaceCondition tests the race condition that causes infinite loops
// This test specifically targets the bug where chunk size is modified during iteration
func TestChunkSplitRaceCondition(t *testing.T) {
	// Create a minimal test case that should trigger the race condition
	// We need a chunk where SplitMaxReduction will be called and modify the chunk size
	
	// Arrange - Create a chunk with size 3 that will trigger SplitMaxReduction
	stackAData := []int{1, 2, 3} // Consecutive numbers that will trigger aPartlySort
	
	ps := stack.NewPushSwapDataWithCapacity(10)
	ps.A.FillFromSlice(stackAData)

	// Create a chunk that will trigger the problematic path in SplitMaxReduction
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3, // This size will trigger SplitMaxReduction logic
	}

	dest := &stack.SplitDest{}

	// Act - This should demonstrate the race condition
	done := make(chan bool, 1)
	
	go func() {
		solver.ChunkSplit(ps, chunk, dest)
		done <- true
	}()

	// Wait for completion or timeout
	select {
	case <-done:
		t.Log("ChunkSplit completed successfully")
	case <-time.After(3 * time.Second):
		t.Fatal("ChunkSplit timed out - RACE CONDITION BUG CONFIRMED!")
	}

	// Log the results
	t.Logf("ChunkSplit completed. Final chunk sizes: MIN=%d, MID=%d, MAX=%d", 
		dest.Min.Size, dest.Mid.Size, dest.Max.Size)
}

// TestChunkSplitSizeDistributionBug tests the specific bug where chunk sizes are incorrectly distributed
// This test targets the bug where MoveFromTo result is not properly stored before SplitMaxReduction
func TestChunkSplitSizeDistributionBug(t *testing.T) {
	// Arrange - Create a chunk with size 3 that will trigger SplitMaxReduction
	// This is the minimal case where the bug manifests
	stackAData := []int{1, 2, 3} // Consecutive numbers that will trigger aPartlySort
	
	ps := stack.NewPushSwapDataWithCapacity(10)
	ps.A.FillFromSlice(stackAData)

	// Create a chunk that will trigger the problematic path in SplitMaxReduction
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3, // This size will trigger SplitMaxReduction logic
	}

	dest := &stack.SplitDest{}

	// Act
	solver.ChunkSplit(ps, chunk, dest)

	// Assert - Check that chunk sizes are correctly distributed
	// With input [1,2,3] and size 3, we expect proper distribution
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 3 {
		t.Errorf("Total chunk size = %d, want 3", totalSize)
	}

	// Log the actual distribution to see the bug
	t.Logf("Chunk size distribution: MIN=%d, MID=%d, MAX=%d (total=%d)", 
		dest.Min.Size, dest.Mid.Size, dest.Max.Size, totalSize)

	// The bug should cause incorrect distribution even though total is correct
	// We expect more balanced distribution, not extreme cases like 0,2,1
	if dest.Min.Size == 0 && dest.Mid.Size == 2 && dest.Max.Size == 1 {
		t.Log("BUG DETECTED: Chunk sizes are incorrectly distributed due to race condition")
		t.Log("This confirms the bug where MoveFromTo result is not properly stored")
	} else {
		t.Log("Chunk sizes are correctly distributed - bug may be fixed")
	}
}

// TestChunkSplitSize11 tests chunk_split with real data from logs - chunk size 11
// Log reference: Line 470-480 - Splitting chunk: loc=0, size=11 with Stack A [98 91 93 90 97 96 99 95 100 92 94]
func TestChunkSplitSize11(t *testing.T) {
	// Arrange - EXACT data from log line 470-480
	// Stack A elements from log: [98 91 93 90 97 96 99 95 100 92 94]
	stackAData := []int{98, 91, 93, 90, 97, 96, 99, 95, 100, 92, 94}

	// Stack B elements from log: [82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73]
	stackBData := []int{82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state from log - chunk size 11, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 11, // EXACT from log - chunk size 11
	}

	dest := &stack.SplitDest{}

	// Act
	solver.ChunkSplit(ps, chunk, dest)

	// Assert - EXACT results from log line 480
	// Expected: MIN=0, MID=8, MAX=3 (from log)
	if dest.Min.Size != 0 {
		t.Errorf("Min chunk size = %d, want 0 (from log line 480)", dest.Min.Size)
	}
	if dest.Mid.Size != 8 {
		t.Errorf("Mid chunk size = %d, want 8 (from log line 480)", dest.Mid.Size)
	}
	if dest.Max.Size != 3 {
		t.Errorf("Max chunk size = %d, want 3 (from log line 480)", dest.Max.Size)
	}

	// Check that sizes sum to original chunk size
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 11 {
		t.Errorf("Total split size = %d, want 11 (from log line 470)", totalSize)
	}

	t.Logf("Chunk split size 11 completed successfully: MIN=%d, MID=%d, MAX=%d", 
		dest.Min.Size, dest.Mid.Size, dest.Max.Size)
}
