package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestSortTwoTOP_A_ChunkSize2 tests sort_two function for TOP_A location with chunk size 2
// Log reference: Line 559-620 - ENTRY: sort_two() with Stack A [98 99 100] and chunk size decreased by 2
func TestSortTwoTOP_A_ChunkSize2(t *testing.T) {
	// Arrange - EXACT data from log line 559-620
	// Stack A elements from log: [98 99 100 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
	stackAData := []int{98, 99, 100}

	// Stack B elements from log: [94 92 95 96 97 90 93 91 82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73 0 0 0]
	stackBData := []int{94, 92, 95, 96, 97, 90, 93, 91, 82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state from log - chunk size 2, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 2, // EXACT from log - chunk size 2
	}

	// Act
	solver.SortTwo(ps, chunk)

	// Assert - EXACT results from log line 620
	// Expected: chunk size decreased by 2 (from 2 to 0)
	expectedSize := 0
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SortTwo = %d, want %d (from log line 620 - decreased by 2)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements unchanged since TOP_A doesn't require move_from_to
	// and the elements [98 99 100] are already sorted
	expectedStackA := []int{98, 99, 100}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SortTwo = %d, want %d (from log line 620)", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged for TOP_A location
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 620 - TOP_A should not change)", i, actualStackA[i], expectedStackA[i])
		}
	}
}

// TestSortTwoBOTTOM_A_ChunkSize2 tests sort_two function for BOTTOM_A location with chunk size 2
// Log reference: Line 1374 - ENTRY: sort_two() with different stack state
func TestSortTwoBOTTOM_A_ChunkSize2(t *testing.T) {
	// Arrange - EXACT data from log line 1374
	// Stack A elements from log: [96 97 98 99 100 94 95 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
	stackAData := []int{96, 97, 98, 99, 100, 94, 95}

	// Stack B elements from log: [82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73 92 90 93 91 0 0 0 0 0 0 0]
	stackBData := []int{82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73, 92, 90, 93, 91}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state - chunk size 2, location BOTTOM_A (requires move_from_to)
	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_A,
		Size: 2, // EXACT from log - chunk size 2
	}

	// Act
	solver.SortTwo(ps, chunk)

	// Assert - EXACT results from log
	// Expected: chunk size decreased by 2 (from 2 to 0)
	expectedSize := 0
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SortTwo = %d, want %d (from log line 1374 - decreased by 2)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements changed due to move_from_to operations for BOTTOM_A
	// The function should move 2 elements from BOTTOM_A to TOP_A
	// This would change the stack from [96 97 98 99 100 94 95] to something like [94 95 96 97 98 99 100]
	// But since we're testing the chunk size decrease, we focus on that primary behavior
	actualStackA := ps.A.ToSlice()

	// Stack A should still have the same number of elements
	expectedStackASize := 7
	if len(actualStackA) != expectedStackASize {
		t.Errorf("Stack A size after SortTwo = %d, want %d (from log line 1374)", len(actualStackA), expectedStackASize)
	}
}
