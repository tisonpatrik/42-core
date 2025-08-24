package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestEasySortWithRealData tests EasySort function using real data from logs
// Log reference: Line 9727+ - Stack state before and after easy_sort operation
func TestEasySortWithRealData(t *testing.T) {
	// Arrange - EXACT data from log line 9727+
	// Stack A elements from log line 9727+: [100 56 95 41 62 54 31 17 72 4 90 1 15 30 82 92 24 60 44 43 13 98 50 99 96 28 38 3 64 53 58 51 32 84 47 75 71 86 80 18 76 94 78 89 83 93 91 70 74 79 81 97 88 73 68 69 85 87 77]
	stackAData := []int{100, 56, 95, 41, 62, 54, 31, 17, 72, 4, 90, 1, 15, 30, 82, 92, 24, 60, 44, 43, 13, 98, 50, 99, 96, 28, 38, 3, 64, 53, 58, 51, 32, 84, 47, 75, 71, 86, 80, 18, 76, 94, 78, 89, 83, 93, 91, 70, 74, 79, 81, 97, 88, 73, 68, 69, 85, 87, 77}
	
	// Stack B elements from log line 9727+: [63 45 46 55 40 66 36 57 59 52 49 48 61 42 37 39 65 67 35 6 34 2 12 14 9 22 25 19 23 11 29 16 5 33 10 27 8 26 21 20 7]
	stackBData := []int{63, 45, 46, 55, 40, 66, 36, 57, 59, 52, 49, 48, 61, 42, 37, 39, 65, 67, 35, 6, 34, 2, 12, 14, 9, 22, 25, 19, 23, 11, 29, 16, 5, 33, 10, 27, 8, 26, 21, 20, 7}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state from log - chunk size 3, location TOP_B (since we're moving from B to A)
	chunk := &stack.Chunk{
		Loc:  stack.TOP_B,
		Size: 3, // EXACT from log - chunk size 3
	}

	// Act
	solver.EasySort(ps, chunk)

	// Assert - EXACT results from log line 9727+
	// Expected: chunk size should remain unchanged since no elements were moved
	// Condition: value(&data->a, 1) == chunk_value(data, to_sort, 2) + 1 was NOT met (100 ≠ 63+1)
	expectedChunkSize := 3 // No change expected - no movement occurred
	if chunk.Size != expectedChunkSize {
		t.Errorf("Chunk size after EasySort = %d, want %d (from log line 9727+ - no movement should not change size)", chunk.Size, expectedChunkSize)
	}

	// Expected: Stack A should remain unchanged [100 56 95 41 62 54 31 17 72 4 90 1 15 30 82 92 24 60 44 43 13 98 50 99 96 28 38 3 64 53 58 51 32 84 47 75 71 86 80 18 76 94 78 89 83 93 91 70 74 79 81 97 88 73 68 69 85 87 77]
	expectedStackA := []int{100, 56, 95, 41, 62, 54, 31, 17, 72, 4, 90, 1, 15, 30, 82, 92, 24, 60, 44, 43, 13, 98, 50, 99, 96, 28, 38, 3, 64, 53, 58, 51, 32, 84, 47, 75, 71, 86, 80, 18, 76, 94, 78, 89, 83, 93, 91, 70, 74, 79, 81, 97, 88, 73, 68, 69, 85, 87, 77}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after EasySort = %d, want %d (from log line 9727+)", len(actualStackA), len(expectedStackA))
	}

	// Check first 60 elements of Stack A (the ones we care about)
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 9727+ - should remain unchanged)", i, actualStackA[i], expectedStackA[i])
		}
	}

	// Expected: Stack B should remain unchanged [63 45 46 55 40 66 36 57 59 52 49 48 61 42 37 39 65 67 35 6 34 2 12 14 9 22 25 19 23 11 29 16 5 33 10 27 8 26 21 20 7]
	expectedStackB := []int{63, 45, 46, 55, 40, 66, 36, 57, 59, 52, 49, 48, 61, 42, 37, 39, 65, 67, 35, 6, 34, 2, 12, 14, 9, 22, 25, 19, 23, 11, 29, 16, 5, 33, 10, 27, 8, 26, 21, 20, 7}
	actualStackB := ps.B.ToSlice()

	if len(actualStackB) != len(expectedStackB) {
		t.Errorf("Stack B size after EasySort = %d, want %d (from log line 9727+)", len(actualStackB), len(expectedStackB))
	}

	// Check first 41 elements of Stack B (the ones we care about)
	for i := 0; i < len(expectedStackB) && i < len(actualStackB); i++ {
		if actualStackB[i] != expectedStackB[i] {
			t.Errorf("Stack B[%d] = %d, want %d (from log line 9727+ - should remain unchanged)", i, actualStackB[i], expectedStackB[i])
		}
	}

	t.Logf("EasySort tests completed with real data from log line 9727+")
}

// TestEasySortWithConsecutiveElements tests EasySort when elements can be moved consecutively
// This test uses artificial data to test the consecutive movement logic
func TestEasySortWithConsecutiveElements(t *testing.T) {
	// Arrange - Create stack with elements that can be moved consecutively
	// Stack A: [5 6 7 8] (first element = 5)
	// Stack B: [4 3 2 1] (first element = 4, which is 5-1)
	stackAData := []int{5, 6, 7, 8}
	stackBData := []int{4, 3, 2, 1}

	ps := stack.NewPushSwapDataWithCapacity(10)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state - chunk size 2, location TOP_B
	chunk := &stack.Chunk{
		Loc:  stack.TOP_B,
		Size: 2, // Should be decreased by 1 when element 4 is moved
	}

	// Act
	solver.EasySort(ps, chunk)

	// Assert - Expected: chunk size should be decreased by 2 (both consecutive elements moved)
	// Since both conditions were met:
	// 1. value(&data->a, 1) == chunk_value(data, to_sort, 1) + 1 (5 == 4 + 1)
	// 2. value(&data->a, 1) == chunk_value(data, to_sort, 1) + 1 (4 == 3 + 1)
	expectedChunkSize := 0 // Decreased by 2 from 2 (both consecutive elements moved)
	if chunk.Size != expectedChunkSize {
		t.Errorf("Chunk size after EasySort = %d, want %d (both consecutive elements should decrease size to 0)", chunk.Size, expectedChunkSize)
	}

	// Expected: Stack A should now contain [3 4 5 6 7 8] (elements 3 and 4 moved from B to A)
	expectedStackA := []int{3, 4, 5, 6, 7, 8}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after EasySort = %d, want %d", len(actualStackA), len(expectedStackA))
	}

	// Check first 6 elements of Stack A
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (elements 3 and 4 should be moved from B to A)", i, actualStackA[i], expectedStackA[i])
		}
	}

	// Expected: Stack B should now contain [2 1] (elements 3 and 4 removed)
	expectedStackB := []int{2, 1}
	actualStackB := ps.B.ToSlice()

	if len(actualStackB) != len(expectedStackB) {
		t.Errorf("Stack B size after EasySort = %d, want %d", len(actualStackB), len(expectedStackB))
	}

	// Check first 2 elements of Stack B
	for i := 0; i < len(expectedStackB) && i < len(actualStackB); i++ {
		if actualStackB[i] != expectedStackB[i] {
			t.Errorf("Stack B[%d] = %d, want %d (elements 3 and 4 should be removed)", i, actualStackB[i], expectedStackB[i])
		}
	}

	t.Logf("EasySort with consecutive elements tests completed successfully")
}

// TestEasySortNoMovement tests EasySort when no elements can be moved
// This test uses artificial data to test the case when conditions are not met
func TestEasySortNoMovement(t *testing.T) {
	// Arrange - Create stack with elements that cannot be moved
	// Stack A: [10 20 30 40] (first element = 10)
	// Stack B: [5 15 25 35] (no element is 10-1 = 9 or 10-2 = 8)
	stackAData := []int{10, 20, 30, 40}
	stackBData := []int{5, 15, 25, 35}

	ps := stack.NewPushSwapDataWithCapacity(50)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Initial chunk state - chunk size 3, location TOP_B
	chunk := &stack.Chunk{
		Loc:  stack.TOP_B,
		Size: 3, // Should remain unchanged since no elements can be moved
	}

	// Act
	solver.EasySort(ps, chunk)

	// Assert - Expected: chunk size should remain unchanged
	// Since no element in B satisfies the consecutive conditions
	expectedChunkSize := 3 // No change expected
	if chunk.Size != expectedChunkSize {
		t.Errorf("Chunk size after EasySort = %d, want %d (no movement should not change size)", chunk.Size, expectedChunkSize)
	}

	// Expected: Stack A should remain unchanged [10 20 30 40]
	expectedStackA := []int{10, 20, 30, 40}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after EasySort = %d, want %d", len(actualStackA), len(expectedStackA))
	}

	// Check first 4 elements of Stack A
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (should remain unchanged)", i, actualStackA[i], expectedStackA[i])
		}
	}

	// Expected: Stack B should remain unchanged [5 15 25 35]
	expectedStackB := []int{5, 15, 25, 35}
	actualStackB := ps.B.ToSlice()

	if len(actualStackB) != len(expectedStackB) {
		t.Errorf("Stack B size after EasySort = %d, want %d", len(actualStackB), len(expectedStackB))
	}

	// Check first 4 elements of Stack B
	for i := 0; i < len(expectedStackB) && i < len(actualStackB); i++ {
		if actualStackB[i] != expectedStackB[i] {
			t.Errorf("Stack B[%d] = %d, want %d (should remain unchanged)", i, actualStackB[i], expectedStackB[i])
		}
	}

	t.Logf("EasySort no movement tests completed successfully")
}

// TestChunkSortRecursion tests the full recursion of Chunk_sort to catch infinite loops
func TestChunkSortRecursion(t *testing.T) {
	// Arrange - Create a stack with 100 numbers to test deep recursion
	stackAData := []int{100, 56, 95, 41, 62, 54, 31, 17, 72, 4, 90, 1, 15, 30, 82, 92, 24, 60, 44, 43, 13, 98, 50, 99, 96, 28, 38, 3, 64, 53, 58, 51, 32, 84, 47, 75, 71, 86, 80, 18, 76, 94, 78, 89, 83, 93, 91, 70, 74, 79, 81, 97, 88, 73, 68, 69, 85, 87, 77}
	
	// Use proper capacity for 100 numbers
	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	
	t.Logf("Initial stack A: %v", ps.A.GetStack()[:ps.A.Size()])
	t.Logf("Stack A size: %d", ps.A.Size())
	
	// Act - This should trigger the full recursion through RecChunkSort
	t.Log("Calling Chunk_sort - this will trigger recursion...")
	solver.ChunkSort(ps)
	
	// Assert - Check that sorting completed without infinite loop
	t.Logf("Final stack A: %v", ps.A.GetStack()[:ps.A.Size()])
	t.Logf("Final stack A size: %d", ps.A.Size())
	
	// Basic check that we didn't lose elements
	if ps.A.Size() != 59 {
		t.Errorf("Stack A size changed from 69 to %d", ps.A.Size())
	}
	
	t.Log("Chunk_sort completed successfully - no infinite loop detected!")
}
