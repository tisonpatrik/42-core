package algo

import (
	"reflect"
	"testing"
)

func TestFindLISIndices(t *testing.T) {
	tests := []struct {
		name     string
		input    []int
		expected map[int]bool
	}{
		{
			name:     "empty array",
			input:    []int{},
			expected: map[int]bool{},
		},
		{
			name:     "single element",
			input:    []int{5},
			expected: map[int]bool{0: true},
		},
		{
			name:     "already sorted",
			input:    []int{1, 2, 3, 4, 5},
			expected: map[int]bool{0: true, 1: true, 2: true, 3: true, 4: true},
		},
		{
			name:     "reverse sorted",
			input:    []int{5, 4, 3, 2, 1},
			expected: map[int]bool{0: true},
		},
		{
			name:     "mixed array",
			input:    []int{10, 22, 9, 33, 21, 50, 41, 60},
			expected: map[int]bool{0: true, 1: true, 3: true, 5: true, 7: true},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := FindLISIndices(tt.input)
			if !reflect.DeepEqual(result, tt.expected) {
				t.Errorf("FindLISIndices(%v) = %v, want %v", tt.input, result, tt.expected)
			}
		})
	}
}

func TestConvertToIndexSet(t *testing.T) {
	tests := []struct {
		name     string
		input    []int
		expected map[int]bool
	}{
		{
			name:     "empty slice",
			input:    []int{},
			expected: map[int]bool{},
		},
		{
			name:     "single element",
			input:    []int{5},
			expected: map[int]bool{5: true},
		},
		{
			name:     "multiple elements",
			input:    []int{1, 2, 3},
			expected: map[int]bool{1: true, 2: true, 3: true},
		},
		{
			name:     "reverse order",
			input:    []int{3, 2, 1},
			expected: map[int]bool{1: true, 2: true, 3: true},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := convertToIndexSet(tt.input)
			if !reflect.DeepEqual(result, tt.expected) {
				t.Errorf("convertToIndexSet(%v) = %v, want %v", tt.input, result, tt.expected)
			}
		})
	}
}

func TestLISIntegration(t *testing.T) {
	// Test a complex case to ensure the algorithm works correctly
	input := []int{10, 22, 9, 33, 21, 50, 41, 60}
	
	// Expected LIS indices: [0, 1, 3, 5, 7] corresponding to values [10, 22, 33, 50, 60]
	expected := map[int]bool{0: true, 1: true, 3: true, 5: true, 7: true}
	
	result := FindLISIndices(input)
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("LIS integration test failed: got %v, want %v", result, expected)
	}
}
