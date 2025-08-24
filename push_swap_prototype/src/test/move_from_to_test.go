package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestMoveFromToBOTTOM_A_To_TOP_A tests move_from_to function from BOTTOM_A to TOP_A
// Log reference: Line 854-880 - AFTER move_from_to at LINE 150 in sort_one()
// Stack A changed from [95 96 97 98 99 100 94] to [94 95 96 97 98 99 100]
func TestMoveFromToBOTTOM_A_To_TOP_A(t *testing.T) {
	// Arrange - EXACT data from log line 854-880
	// Stack A elements from log: [95 96 97 98 99 100 94 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
	stackAData := []int{95, 96, 97, 98, 99, 100, 94}

	// Stack B elements from log: [82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73 92 90 93 91 0 0 0 0 0 0 0]
	stackBData := []int{82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73, 92, 90, 93, 91}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Act - Move from BOTTOM_A to TOP_A (from log line 150)
	result := solver.MoveFromTo(ps, stack.BOTTOM_A, stack.TOP_A)

	// Assert - EXACT results from log line 880
	// Expected: Stack A elements changed from [95 96 97 98 99 100 94] to [94 95 96 97 98 99 100]
	expectedStackA := []int{94, 95, 96, 97, 98, 99, 100}
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != len(expectedStackA) {
		t.Errorf("Stack A size after MoveFromTo = %d, want %d (from log line 880)", len(actualStackA), len(expectedStackA))
	}

	// Check that elements are moved correctly according to log
	for i := 0; i < len(expectedStackA) && i < len(actualStackA); i++ {
		if actualStackA[i] != expectedStackA[i] {
			t.Errorf("Stack A[%d] = %d, want %d (from log line 880 - move_from_to BOTTOM_A to TOP_A)", i, actualStackA[i], expectedStackA[i])
		}
	}

	// Expected: MoveFromTo should return success (non-zero)
	if result == 0 {
		t.Errorf("MoveFromTo return value = %d, want non-zero (from log line 880 - successful move)", result)
	}
}

// TestMoveFromToTOP_B_To_TOP_A tests move_from_to function from TOP_B to TOP_A
// Log reference: Line 1082 - AFTER move_from_to 1 at LINE 116 in sort_two()
func TestMoveFromToTOP_B_To_TOP_A(t *testing.T) {
	// Arrange - EXACT data from log line 1082
	// Stack A elements from log: [98 99 100 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
	stackAData := []int{98, 99, 100}

	// Stack B elements from log: [94 92 95 96 97 90 93 91 82 84 87 81 83 86 80 85 88 79 89 65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73 0 0 0]
	stackBData := []int{94, 92, 95, 96, 97, 90, 93, 91, 82, 84, 87, 81, 83, 86, 80, 85, 88, 79, 89, 65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)
	ps.B.FillFromSlice(stackBData)

	// Act - Move from TOP_B to TOP_A (from log line 116)
	result := solver.MoveFromTo(ps, stack.TOP_B, stack.TOP_A)

	// Assert - EXACT results from log line 1082
	// Expected: Stack A should have one more element (push from B)
	expectedStackASize := 4 // Original 3 + 1 from B
	actualStackA := ps.A.ToSlice()

	if len(actualStackA) != expectedStackASize {
		t.Errorf("Stack A size after MoveFromTo = %d, want %d (from log line 1082 - push from TOP_B)", len(actualStackA), expectedStackASize)
	}

	// Expected: MoveFromTo should return success (non-zero)
	if result == 0 {
		t.Errorf("MoveFromTo return value = %d, want non-zero (from log line 1082 - successful move)", result)
	}

	// Expected: Stack B should have one less element
	expectedStackBSize := len(stackBData) - 1
	actualStackB := ps.B.ToSlice()

	if len(actualStackB) != expectedStackBSize {
		t.Errorf("Stack B size after MoveFromTo = %d, want %d (from log line 1082 - element moved to A)", len(actualStackB), expectedStackBSize)
	}
}
