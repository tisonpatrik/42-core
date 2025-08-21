package utils

import (
	"reflect"
	"testing"
)

func TestRandomToRank(t *testing.T) {
	// Test with empty slice
	result := RandomToRank([]int{})
	if len(result) != 0 {
		t.Errorf("Expected empty result for empty input, got %v", result)
	}
	
	// Test with single value
	result = RandomToRank([]int{42})
	expected := []int{1} // C implementation gives ranks from 1
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	
	// Test with multiple values
	result = RandomToRank([]int{5, 3, 1, 4, 2})
	// 1 is smallest (rank 1), 2 is second smallest (rank 2), etc.
	// So [5, 3, 1, 4, 2] should become [5, 3, 1, 4, 2]
	expected = []int{5, 3, 1, 4, 2}
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	
	// Test with unique values only (duplicates are handled at input validation)
	result = RandomToRank([]int{3, 1, 2})
	// 1 is smallest (rank 1), 2 is second smallest (rank 2), 3 is largest (rank 3)
	// So [3, 1, 2] should become [3, 1, 2]
	expected = []int{3, 1, 2}
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	
	// Test with negative values
	result = RandomToRank([]int{-5, -3, -1, -4, -2})
	// -5 is smallest (rank 1), -4 is second smallest (rank 2), etc.
	expected = []int{1, 3, 5, 2, 4}
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}
