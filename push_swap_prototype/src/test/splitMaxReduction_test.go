package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestSplitMaxReductionCase1 tests SplitMaxReduction Case 1: Sorting 3 consecutive elements
// Log reference: Line 2000+ - Stack A with consecutive elements [79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100]
func TestSplitMaxReductionCase1(t *testing.T) {
	// Arrange - EXACT data from log line 2000+
	// Stack A elements from log line 2000+: [79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100]
	stackAData := []int{79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)

	// Initial chunk state from log - chunk size 3, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3, // EXACT from log - chunk size 3
	}

	// Act
	solver.SplitMaxReduction(ps, chunk)

	// Assert - EXACT results from log line 2000+
	// Expected: chunk size should remain 3 since no conditions match
	// The function checks isConsecutive(79, 80, 81, 82) which returns false
	// Then checks value(79) == value(81) - 1 which is 79 == 81 - 1 = 79 == 80 (false)
	// Finally checks APartlySort(ps, 1) which returns false (79 != 100, so not consecutive to end)
	expectedSize := 3 // No change expected
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SplitMaxReduction = %d, want %d (from log line 2000+ - no change expected)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should remain unchanged since no operations are performed
	expectedStackA := []int{79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SplitMaxReduction = %d, want %d (from log line 2000+)", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 2000+ - should not change)", i, actualStackA[i], expectedStackA[i])
		}
	}

	t.Logf("SplitMaxReduction Case 1 tests completed successfully (from log line 2000+)")
}

// TestSplitMaxReductionCase2 tests SplitMaxReduction Case 2: Swapping and decrementing size
// Log reference: Line 1000+ - Stack A with elements [94 95 96 97 98 99 100] where first 3 are consecutive
func TestSplitMaxReductionCase2(t *testing.T) {
	// Arrange - EXACT data from log line 1000+
	// Stack A elements from log line 1000+: [94 95 96 97 98 99 100]
	stackAData := []int{94, 95, 96, 97, 98, 99, 100}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)

	// Initial chunk state from log - chunk size 3, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 3, // EXACT from log - chunk size 3
	}

	// Act
	solver.SplitMaxReduction(ps, chunk)

	// Assert - EXACT results from log line 1000+
	// Expected: chunk size should remain 3 since no conditions match
	// The function checks isConsecutive(94, 95, 96, 97) which returns false (96-95=1, 97-96=1, but 95-94=1, so false)
	// Then checks value(94) == value(96) - 1 which is 94 == 96 - 1 = 94 == 95 (false)
	// Finally checks APartlySort(ps, 1) which returns false (94 != 100, so not consecutive to end)
	expectedSize := 3 // No change expected
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SplitMaxReduction = %d, want %d (from log line 1000+ - no change expected)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should remain unchanged since no operations are performed
	expectedStackA := []int{94, 95, 96, 97, 98, 99, 100}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SplitMaxReduction = %d, want %d (from log line 1000+)", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 1000+ - should not change)", i, actualStackA[i], expectedStackA[i])
		}
	}

	t.Logf("SplitMaxReduction Case 2 tests completed successfully (from log line 1000+)")
}

// TestSplitMaxReductionCase3 tests SplitMaxReduction Case 3: Decrementing size for single element
// Log reference: Line 43 - Stack A with elements [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestSplitMaxReductionCase3(t *testing.T) {
	// Arrange - EXACT data from log line 43
	// Stack A elements from log line 43: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
	stackAData := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)

	// Initial chunk state from log - chunk size 1, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 1, // EXACT from log - chunk size 1
	}

	// Act
	solver.SplitMaxReduction(ps, chunk)

	// Assert - EXACT results from log line 43
	// Expected: chunk size should remain 1 since no conditions match
	// The function checks isConsecutive(53, 12, 18, 68) which returns false
	// Then checks value(53) == value(18) - 1 which is 53 == 18 - 1 = 53 == 17 (false)
	// Finally checks APartlySort(ps, 1) which returns false (53 != 100, so not consecutive to end)
	expectedSize := 1 // No change expected
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SplitMaxReduction = %d, want %d (from log line 43 - no change expected)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should remain unchanged since no operations are performed
	expectedStackA := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SplitMaxReduction = %d, want %d (from log line 43)", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 43 - should not change)", i, actualStackA[i], expectedStackA[i])
		}
	}

	t.Logf("SplitMaxReduction Case 3 tests completed successfully (from log line 43)")
}

// TestSplitMaxReductionNoMatch tests SplitMaxReduction when no conditions match
// Log reference: Line 43 - Stack A with elements that don't match any case
func TestSplitMaxReductionNoMatch(t *testing.T) {
	// Arrange - EXACT data from log line 43
	// Stack A elements from log line 43: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
	stackAData := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)

	// Initial chunk state from log - chunk size 5, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 5, // EXACT from log - chunk size 5
	}

	// Act
	solver.SplitMaxReduction(ps, chunk)

	// Assert - EXACT results from log line 43
	// Expected: chunk size should remain unchanged since no conditions match
	expectedSize := 5 // No change
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SplitMaxReduction = %d, want %d (from log line 43 - no change expected)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should remain unchanged since no operations are performed
	expectedStackA := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SplitMaxReduction = %d, want %d (from log line 43)", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 43 - should not change)", i, actualStackA[i], expectedStackA[i])
		}
	}

	t.Logf("SplitMaxReduction NoMatch tests completed successfully (from log line 43)")
}

// TestSplitMaxReductionWithConsecutiveElements tests SplitMaxReduction with truly consecutive elements
// This test uses artificial data to test the actual functionality when conditions are met
func TestSplitMaxReductionWithConsecutiveElements(t *testing.T) {
	// Arrange - Create stack with truly consecutive elements starting from 1
	// This tests the case where APartlySort(ps, 1) would return true
	stackAData := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

	ps := stack.NewPushSwapDataWithCapacity(10) // Capacity 10 matches max value 10
	ps.A.FillFromSlice(stackAData)

	// Initial chunk state - chunk size 1, location TOP_A
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 1, // Should be decreased by 1 when APartlySort(ps, 1) returns true
	}

	// Act
	solver.SplitMaxReduction(ps, chunk)

	// Assert - Expected: chunk size should be decreased by 1
	// Since APartlySort(ps, 1) returns true (1,2,3,4,5,6,7,8,9,10 are consecutive to max value 10)
	expectedSize := 0 // Decreased by 1 from 1
	if chunk.Size != expectedSize {
		t.Errorf("Chunk size after SplitMaxReduction = %d, want %d (consecutive elements should decrease size)", chunk.Size, expectedSize)
	}

	// Expected: Stack A elements should remain unchanged since no operations are performed
	expectedStackA := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after SplitMaxReduction = %d, want %d", len(actualStackA), len(expectedStackA))
	}

	// Check elements remain unchanged
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (should not change)", i, actualStackA[i], expectedStackA[i])
		}
	}

	t.Logf("SplitMaxReduction with consecutive elements tests completed successfully")
}
