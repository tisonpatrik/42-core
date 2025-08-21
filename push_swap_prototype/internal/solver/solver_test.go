package solver

import (
	"push_swap_prototype/internal/operations"
	"push_swap_prototype/internal/utils"
	"testing"
)

// TestSolvePushSwapEmpty tests SolvePushSwap with empty input
func TestSolvePushSwapEmpty(t *testing.T) {
	numbers := []int{}
	ops, result := SolvePushSwap(numbers)
	
	// Should return no operations and empty result
	if len(ops) != 0 {
		t.Errorf("Expected no operations for empty input, got %d", len(ops))
	}
	if len(result) != 0 {
		t.Errorf("Expected empty result for empty input, got %d elements", len(result))
	}
}

// TestSolvePushSwapSingleElement tests SolvePushSwap with single element
func TestSolvePushSwapSingleElement(t *testing.T) {
	numbers := []int{42}
	ops, result := SolvePushSwap(numbers)
	
	// Should return no operations and same element
	if len(ops) != 0 {
		t.Errorf("Expected no operations for single element, got %d", len(ops))
	}
	if len(result) != 1 {
		t.Errorf("Expected 1 element in result, got %d", len(result))
	}
	// Note: InitializeFromSlice converts numbers to ranks, so 42 becomes 1
	if result[0] != 1 {
		t.Errorf("Expected result [1] (ranked), got %v", result)
	}
}

// TestSolvePushSwapAlreadySorted tests SolvePushSwap with already sorted input
func TestSolvePushSwapAlreadySorted(t *testing.T) {
	numbers := []int{1, 2, 3, 4, 5}
	ops, result := SolvePushSwap(numbers)
	
	// Should return no operations and same result
	if len(ops) != 0 {
		t.Errorf("Expected no operations for already sorted input, got %d", len(ops))
	}
	if len(result) != 5 {
		t.Errorf("Expected 5 elements in result, got %d", len(result))
	}
	
	// Verify result is still sorted
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
}

// TestSolvePushSwapThreeElements tests SolvePushSwap with three elements
func TestSolvePushSwapThreeElements(t *testing.T) {
	numbers := []int{3, 1, 2}
	ops, result := SolvePushSwap(numbers)
	
	// Should return some operations and sorted result
	if len(ops) == 0 {
		t.Errorf("Expected operations for unsorted three elements, got none")
	}
	if len(result) != 3 {
		t.Errorf("Expected 3 elements in result, got %d", len(result))
	}
	
	// Verify result is sorted
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range numbers {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSolvePushSwapFiveElements tests SolvePushSwap with five elements
func TestSolvePushSwapFiveElements(t *testing.T) {
	numbers := []int{5, 2, 4, 1, 3}
	ops, result := SolvePushSwap(numbers)
	
	// Should return some operations and sorted result
	if len(ops) == 0 {
		t.Errorf("Expected operations for unsorted five elements, got none")
	}
	if len(result) != 5 {
		t.Errorf("Expected 5 elements in result, got %d", len(result))
	}
	
	// Verify result is sorted
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range numbers {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSolvePushSwapLargeInput tests SolvePushSwap with large input
func TestSolvePushSwapLargeInput(t *testing.T) {
	numbers := []int{8, 3, 6, 1, 5, 2, 7, 4}
	ops, result := SolvePushSwap(numbers)
	
	// Should return some operations and sorted result
	if len(ops) == 0 {
		t.Errorf("Expected operations for unsorted large input, got none")
	}
	if len(result) != 8 {
		t.Errorf("Expected 8 elements in result, got %d", len(result))
	}
	
	// Verify result is sorted
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range numbers {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSortThreeA tests sort_three_a function directly
func TestSortThreeA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{3, 1, 2})
	
	sort_three_a(ps)
	
	// Should have 3 elements
	if ps.A.Size() != 3 {
		t.Errorf("Expected 3 elements in stack A, got %d", ps.A.Size())
	}
	
	// Should be sorted
	result := ps.A.ToSlice()
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range []int{3, 1, 2} {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSortThreeAAlreadySorted tests sort_three_a with already sorted input
func TestSortThreeAAlreadySorted(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{1, 2, 3})
	
	originalResult := ps.A.ToSlice()
	sort_three_a(ps)
	
	// Should remain unchanged
	result := ps.A.ToSlice()
	if len(result) != 3 {
		t.Errorf("Expected 3 elements, got %d", len(result))
	}
	
	// Should still be sorted
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Should be the same as original
	for i, val := range result {
		if val != originalResult[i] {
			t.Errorf("Expected unchanged result, got %v instead of %v", result, originalResult)
			break
		}
	}
}

// TestSortThreeAReverseSorted tests sort_three_a with reverse sorted input
func TestSortThreeAReverseSorted(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{3, 2, 1})
	
	sort_three_a(ps)
	
	// Should have 3 elements
	if ps.A.Size() != 3 {
		t.Errorf("Expected 3 elements in stack A, got %d", ps.A.Size())
	}
	
	// Should be sorted
	result := ps.A.ToSlice()
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range []int{3, 2, 1} {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSortThreeAEdgeCases tests sort_three_a with various edge cases
func TestSortThreeAEdgeCases(t *testing.T) {
	testCases := [][]int{
		{2, 3, 1}, // Middle element is largest
		{1, 3, 2}, // First element is smallest
		{2, 1, 3}, // Last element is largest
	}
	
	for _, numbers := range testCases {
		t.Run("", func(t *testing.T) {
			ps := operations.NewPushSwapDataWithCapacity(4)
			ps.A.FillFromSlice(numbers)
			
			sort_three_a(ps)
			
			// Should have 3 elements
			if ps.A.Size() != 3 {
				t.Errorf("Expected 3 elements in stack A, got %d", len(numbers))
			}
			
			// Should be sorted
			result := ps.A.ToSlice()
			if !utils.IsSorted(result) {
				t.Errorf("Expected sorted result for %v, got %v", numbers, result)
			}
			
			// Verify all original elements are present
			originalSet := make(map[int]bool)
			for _, num := range numbers {
				originalSet[num] = true
			}
			for _, num := range result {
				if !originalSet[num] {
					t.Errorf("Result contains element %d not in original input %v", num, numbers)
				}
			}
		})
	}
}

// TestSortFiveA tests sort_five_a function directly
func TestSortFiveA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{5, 2, 4, 1, 3})
	
	sort_five_a(ps)
	
	// Should have 5 elements
	if ps.A.Size() != 5 {
		t.Errorf("Expected 5 elements in stack A, got %d", ps.A.Size())
	}
	
	// Should be sorted
	result := ps.A.ToSlice()
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range []int{5, 2, 4, 1, 3} {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSortFiveAAlreadySorted tests sort_five_a with already sorted input
func TestSortFiveAAlreadySorted(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5})
	
	originalResult := ps.A.ToSlice()
	sort_five_a(ps)
	
	// Should remain unchanged
	result := ps.A.ToSlice()
	if len(result) != 5 {
		t.Errorf("Expected 5 elements, got %d", len(result))
	}
	
	// Should still be sorted
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Should be the same as original
	for i, val := range result {
		if val != originalResult[i] {
			t.Errorf("Expected unchanged result, got %v instead of %v", result, originalResult)
			break
		}
	}
}

// TestSortFiveAReverseSorted tests sort_five_a with reverse sorted input
func TestSortFiveAReverseSorted(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{5, 4, 3, 2, 1})
	
	sort_five_a(ps)
	
	// Should have 5 elements
	if ps.A.Size() != 5 {
		t.Errorf("Expected 5 elements in stack A, got %d", ps.A.Size())
	}
	
	// Should be sorted
	result := ps.A.ToSlice()
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range []int{5, 4, 3, 2, 1} {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSortFiveAWithOnesAndTwos tests sort_five_a with 1s and 2s at top
func TestSortFiveAWithOnesAndTwos(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{1, 5, 2, 4, 3})
	
	sort_five_a(ps)
	
	// Should have 5 elements
	if ps.A.Size() != 5 {
		t.Errorf("Expected 5 elements in stack A, got %d", ps.A.Size())
	}
	
	// Should be sorted
	result := ps.A.ToSlice()
	if !utils.IsSorted(result) {
		t.Errorf("Expected sorted result, got %v", result)
	}
	
	// Verify all original elements are present
	originalSet := make(map[int]bool)
	for _, num := range []int{1, 5, 2, 4, 3} {
		originalSet[num] = true
	}
	for _, num := range result {
		if !originalSet[num] {
			t.Errorf("Result contains element %d not in original input", num)
		}
	}
}

// TestSortFiveAEdgeCases tests sort_five_a with various edge cases
func TestSortFiveAEdgeCases(t *testing.T) {
	testCases := [][]int{
		{2, 1, 5, 4, 3}, // 1 and 2 at beginning
		{5, 4, 3, 2, 1}, // Reverse order
		{1, 2, 3, 5, 4}, // Almost sorted
		{3, 2, 1, 5, 4}, // First three reversed
	}
	
	for _, numbers := range testCases {
		t.Run("", func(t *testing.T) {
			ps := operations.NewPushSwapDataWithCapacity(6)
			ps.A.FillFromSlice(numbers)
			
			sort_five_a(ps)
			
			// Should have 5 elements
			if ps.A.Size() != 5 {
				t.Errorf("Expected 5 elements in stack A, got %d", len(numbers))
			}
			
			// Should be sorted
			result := ps.A.ToSlice()
			if !utils.IsSorted(result) {
				t.Errorf("Expected sorted result for %v, got %v", numbers, result)
			}
			
			// Verify all original elements are present
			originalSet := make(map[int]bool)
			for _, num := range numbers {
				originalSet[num] = true
			}
			for _, num := range result {
				if !originalSet[num] {
					t.Errorf("Result contains element %d not in original input %v", num, numbers)
				}
			}
		})
	}
}

// TestSolvePushSwapIntegration tests the complete solver with various inputs
func TestSolvePushSwapIntegration(t *testing.T) {
	testCases := []struct {
		name     string
		numbers  []int
		expected []int
	}{
		{"Empty", []int{}, []int{}},
		{"Single", []int{42}, []int{1}}, // 42 becomes rank 1
		{"Two", []int{2, 1}, []int{1, 2}}, // 2 becomes rank 2, 1 becomes rank 1
		{"Three", []int{3, 1, 2}, []int{1, 2, 3}}, // 3 becomes rank 3, 1 becomes rank 1, 2 becomes rank 2
		{"Five", []int{5, 2, 4, 1, 3}, []int{1, 2, 3, 4, 5}}, // All become their ranks
		{"Large", []int{8, 3, 6, 1, 5, 2, 7, 4}, []int{1, 2, 3, 4, 5, 6, 7, 8}}, // All become their ranks
		{"AlreadySorted", []int{1, 2, 3, 4, 5}, []int{1, 2, 3, 4, 5}}, // Already in rank order
		{"ReverseSorted", []int{5, 4, 3, 2, 1}, []int{1, 2, 3, 4, 5}}, // All become their ranks
	}
	
	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			ops, result := SolvePushSwap(tc.numbers)
			
			// Check result length
			if len(result) != len(tc.expected) {
				t.Errorf("Expected %d elements, got %d", len(tc.expected), len(result))
			}
			
			// Check if result is sorted
			if !utils.IsSorted(result) {
				t.Errorf("Expected sorted result, got %v", result)
			}
			
			// Check if result matches expected
			for i, val := range result {
				if val != tc.expected[i] {
					t.Errorf("Expected %v, got %v", tc.expected, result)
					break
				}
			}
			
			// For already sorted inputs, should have no operations
			if utils.IsSorted(tc.numbers) && len(ops) != 0 {
				t.Errorf("Expected no operations for already sorted input, got %d", len(ops))
			}
			
			// For unsorted inputs, should have some operations (except single element)
			if !utils.IsSorted(tc.numbers) && len(tc.numbers) > 1 && len(ops) == 0 {
				t.Errorf("Expected operations for unsorted input, got none")
			}
		})
	}
}
