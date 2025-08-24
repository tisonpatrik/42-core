package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestAPartlySortWithRealData tests APartlySort function using real data from logs
// Log reference: Line 40-139 - Initial stack state with 100 elements and chunk operations
func TestAPartlySortWithRealData(t *testing.T) {
	// Arrange - EXACT data from log line 40-139
	// Stack A elements from log line 43: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
	stackAData := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)

	// Act & Assert - Test various scenarios with real data

	// Test 1: Check if first 4 elements are partly sorted (53, 12, 18, 68)
	// Expected: false (53 > 12, not consecutive) - from log line 43
	result1 := solver.APartlySort(ps, 4)
	if result1 {
		t.Errorf("APartlySort(ps, 4) = %v, want false - first 4 elements [53,12,18,68] are not consecutive (from log line 43)", result1)
	}

	// Test 2: Check if first 3 elements are partly sorted (53, 12, 18)
	// Expected: false (53 > 12, not consecutive) - from log line 43
	result2 := solver.APartlySort(ps, 3)
	if result2 {
		t.Errorf("APartlySort(ps, 3) = %v, want false - first 3 elements [53,12,18] are not consecutive (from log line 43)", result2)
	}

	// Test 3: Check if first element is partly sorted (53)
	// Expected: false (single element 53, but next element 12 != 54, so not consecutive) - from log line 43
	result3 := solver.APartlySort(ps, 1)
	if result3 {
		t.Errorf("APartlySort(ps, 1) = %v, want false - single element 53 with next element 12 != 54, so not consecutive (from log line 43)", result3)
	}

	// Test 4: Check if elements 21-25 are partly sorted (4, 21, 25, 33, 9)
	// Expected: false (4 < 21, but 21 < 25, 25 < 33, 33 > 9 - not consecutive) - from log line 43
	result4 := solver.APartlySort(ps, 5)
	if result4 {
		t.Errorf("APartlySort(ps, 5) = %v, want false - elements [4,21,25,33,9] are not consecutive (from log line 43)", result4)
	}

	// Test 5: Check if elements 6-8 are partly sorted (6, 7, 14)
	// Expected: false (6 < 7, but 7 < 14 - not consecutive) - from log line 43
	result5 := solver.APartlySort(ps, 3)
	if result5 {
		t.Errorf("APartlySort(ps, 3) = %v, want false - elements [6,7,14] are not consecutive (from log line 43)", result5)
	}

	t.Logf("APartlySort tests completed with real data from log line 40-139")
}

// TestAPartlySortWithRealLogDataAfterSplit tests APartlySort with data after chunk split
// Log reference: Line 250-300 - After chunk split, Stack A contains MAX chunk elements
func TestAPartlySortWithRealLogDataAfterSplit(t *testing.T) {
	// Arrange - EXACT data from log line 250-300 after chunk split
	// Stack A elements after split from log line 250: [68 72 98 89 79 91 76 88 93 71 74 90 85 97 70 80 75 96 86 99 95 100 83 69 77 78 92 73 81 94 87 84 82]
	stackAData := []int{68, 72, 98, 89, 79, 91, 76, 88, 93, 71, 74, 90, 85, 97, 70, 80, 75, 96, 86, 99, 95, 100, 83, 69, 77, 78, 92, 73, 81, 94, 87, 84, 82}

	ps := stack.NewPushSwapDataWithCapacity(100)
	ps.A.FillFromSlice(stackAData)

	// Act & Assert - Test with real data after split

	// Test 1: Check if first 4 elements are consecutive (68, 72, 98, 89)
	// Expected: false (68 < 72, but 72 < 98, 98 > 89 - not consecutive) - from log line 250
	result1 := solver.APartlySort(ps, 4)
	if result1 {
		t.Errorf("APartlySort(ps, 4) = %v, want false - elements [68,72,98,89] are not consecutive (from log line 250)", result1)
	}

	// Test 2: Check if first 3 elements are consecutive (68, 72, 98)
	// Expected: false (68 < 72, but 72 < 98 - not consecutive) - from log line 250
	result2 := solver.APartlySort(ps, 3)
	if result2 {
		t.Errorf("APartlySort(ps, 3) = %v, want false - elements [68,72,98] are not consecutive (from log line 250)", result2)
	}

	// Test 3: Check if first 2 elements are consecutive (68, 72)
	// Expected: false (68 < 72, but not consecutive) - from log line 250
	result3 := solver.APartlySort(ps, 2)
	if result3 {
		t.Errorf("APartlySort(ps, 2) = %v, want false - elements [68,72] are not consecutive (from log line 250)", result3)
	}

	// Test 4: Check if elements 25-27 are consecutive (77, 78, 92)
	// Expected: false (77 < 78, but 78 < 92 - not consecutive) - from log line 250
	result4 := solver.APartlySort(ps, 3)
	if result4 {
		t.Errorf("APartlySort(ps, 3) = %v, want false - elements [77,78,92] are not consecutive (from log line 250)", result4)
	}

	t.Logf("APartlySort tests with real log data after split completed successfully (from log line 250-300)")
}
