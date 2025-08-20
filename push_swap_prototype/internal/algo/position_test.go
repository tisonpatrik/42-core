package algo

import "testing"

func TestFindTargetPosition(t *testing.T) {
	tests := []struct {
		name     string
		array    []int
		value    int
		expected int
	}{
		{
			name:     "Empty array",
			array:    []int{},
			value:    5,
			expected: 0,
		},
		{
			name:     "Single element - value smaller",
			array:    []int{10},
			value:    5,
			expected: 0,
		},
		{
			name:     "Single element - value larger",
			array:    []int{3},
			value:    5,
			expected: 1,
		},
		{
			name:     "Two elements - insert at beginning",
			array:    []int{8, 12},
			value:    5,
			expected: 0,
		},
		{
			name:     "Two elements - insert in middle",
			array:    []int{3, 8},
			value:    5,
			expected: 1,
		},
		{
			name:     "Two elements - insert at end",
			array:    []int{2, 4},
			value:    5,
			expected: 2,
		},
		{
			name:     "Multiple elements - insert at beginning",
			array:    []int{10, 15, 20, 25},
			value:    5,
			expected: 0,
		},
		{
			name:     "Multiple elements - insert in middle",
			array:    []int{5, 10, 20, 25},
			value:    15,
			expected: 2,
		},
		{
			name:     "Multiple elements - insert at end",
			array:    []int{5, 10, 15, 20},
			value:    25,
			expected: 4,
		},
		{
			name:     "Duplicate values - insert before first bigger",
			array:    []int{5, 10, 10, 15, 20},
			value:    10,
			expected: 3,
		},
		{
			name:     "All values smaller - insert at end",
			array:    []int{1, 2, 3, 4},
			value:    5,
			expected: 4,
		},
		{
			name:     "All values bigger - insert at beginning",
			array:    []int{10, 20, 30, 40},
			value:    5,
			expected: 0,
		},
		{
			name:     "Negative values",
			array:    []int{-10, -5, 0, 5, 10},
			value:    -15,
			expected: 0,
		},
		{
			name:     "Negative value in middle",
			array:    []int{-10, -5, 0, 5, 10},
			value:    -7,
			expected: 1,
		},
		{
			name:     "Zero value",
			array:    []int{-5, -2, 3, 7},
			value:    0,
			expected: 2,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := FindTargetPosition(tt.array, tt.value)
			if result != tt.expected {
				t.Errorf("FindTargetPosition(%v, %d) = %d, want %d", 
					tt.array, tt.value, result, tt.expected)
			}
		})
	}
}

func TestFindTargetPositionEdgeCases(t *testing.T) {
	// Test with very large arrays
	t.Run("Large array", func(t *testing.T) {
		arr := make([]int, 1000)
		for i := range arr {
			arr[i] = i * 2 // Even numbers: 0, 2, 4, 6, ...
		}
		
		// Test inserting odd numbers
		result := FindTargetPosition(arr, 5)
		expected := 3 // Should go after 4, before 6
		if result != expected {
			t.Errorf("Large array test failed: got %d, want %d", result, expected)
		}
	})
	
	// Test with repeated values
	t.Run("Repeated values", func(t *testing.T) {
		arr := []int{1, 1, 1, 2, 2, 3, 3, 3}
		result := FindTargetPosition(arr, 1)
		expected := 3 // Should go after the last 1, before the first 2
		if result != expected {
			t.Errorf("Repeated values test failed: got %d, want %d", result, expected)
		}
	})
	
	// Test boundary conditions
	t.Run("Boundary conditions", func(t *testing.T) {
		arr := []int{1, 3, 5, 7, 9}
		
		// Test inserting exactly at boundaries
		if pos := FindTargetPosition(arr, 0); pos != 0 {
			t.Errorf("Insert 0: got %d, want 0", pos)
		}
		if pos := FindTargetPosition(arr, 10); pos != 5 {
			t.Errorf("Insert 10: got %d, want 5", pos)
		}
		if pos := FindTargetPosition(arr, 4); pos != 2 {
			t.Errorf("Insert 4: got %d, want 2", pos)
		}
	})
}

func BenchmarkFindTargetPosition(b *testing.B) {
	// Create a test array
	arr := make([]int, 1000)
	for i := range arr {
		arr[i] = i * 2
	}
	
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		FindTargetPosition(arr, 999) // Insert odd number
	}
}
