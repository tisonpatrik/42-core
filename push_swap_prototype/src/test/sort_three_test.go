package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestSortThreeTOP_A_ChunkSize3 tests sort_three function for TOP_A location with chunk size 3
// Log reference: Line 59 - ENTRY: sort_three() with Stack A [98 99 100] and chunk size 3
func TestSortThreeTOP_A_ChunkSize3(t *testing.T) {
	// Arrange - EXACT data from log line 59
	// Stack A elements from log: [98 99 100 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
	stackAData := []int{98, 99, 100}

	// Stack B elements from log: [94 92 95 96 97 90 93 91 82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73 0 0 0]
	stackBData := []int{94, 92, 95, 96, 97, 90, 93, 91, 82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state from log - chunk size 3, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3, // EXACT from log - chunk size 3
	}

	// Act
	solver.SortThree(ps, chunk)

	// Assert - EXACT results from log line 62
	// Expected: chunk size decreased by 3 (from 3 to 0) since SortThree calls SortTwo which decreases by 2, and SortThree decreases by 1
	expectedSize := 0
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SortThree = %d, want %d (from log line 62 - decreased by 3)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should be sorted [98 99 100] -> [98 99 100] (already sorted)
	// The TOP_A location doesn't require move_from_to operations
	expectedStackA := []int{98, 99, 100}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SortThree = %d, want %d (from log line 62)", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged for TOP_A location since they're already sorted
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 62 - TOP_A should not change when already sorted)", i, actualStackA[i], expectedStackA[i])
		}
	}
}

// TestSortThreeTOP_A_ChunkSize3_Unsorted tests sort_three function for TOP_A location with unsorted elements
// Log reference: Line 59 - ENTRY: sort_three() with different stack state
func TestSortThreeTOP_A_ChunkSize3_Unsorted(t *testing.T) {
	// Arrange - Test case for unsorted TOP_A elements
	// Stack A elements: [100 98 99] (unsorted)
	stackAData := []int{100, 98, 99}

	// Stack B elements: [94 92 95 96 97 90 93 91 82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73]
	stackBData := []int{94, 92, 95, 96, 97, 90, 93, 91, 82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state - chunk size 3, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3, // EXACT from log - chunk size 3
	}

	// Act
	solver.SortThree(ps, chunk)

	// Assert - EXACT results from log
	// Expected: chunk size decreased by 3 (from 3 to 0)
	expectedSize := 0
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SortThree = %d, want %d (from log line 59 - decreased by 3)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should be sorted [100 98 99] -> [98 99 100]
	// The TOP_A location will sort the elements in place
	expectedStackA := []int{98, 99, 100}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SortThree = %d, want %d (from log line 59)", len(actualStackA), len(expectedStackA))
	}

	// Check elements are sorted correctly
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 59 - TOP_A should be sorted)", i, actualStackA[i], expectedStackA[i])
		}
	}
}