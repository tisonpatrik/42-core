package stack

import (
	"testing"
)

// TestCurrentSize tests the CurrentSize function (equivalent to current_size in C)
func TestCurrentSize(t *testing.T) {
	tests := []struct {
		name     string
		capacity int
		values   []int
		top      int
		bottom   int
		expected int
	}{
		{
			name:     "normal_stack",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			expected: 5,
		},
		{
			name:     "empty_stack",
			capacity: 5,
			values:   []int{0, 0, 0, 0, 0},
			top:      0,
			bottom:   0,
			expected: 0,
		},
		{
			name:     "wrapped_stack",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      3,
			bottom:   2,
			expected: 5,
		},
		{
			name:     "single_element",
			capacity: 5,
			values:   []int{42, 0, 0, 0, 0},
			top:      0,
			bottom:   0,
			expected: 1,
		},
		{
			name:     "reversed_indices",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      4,
			bottom:   0,
			expected: 2,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			s := New()
			s.InitWithCapacity(tt.capacity)
			s.top = tt.top
			s.bottom = tt.bottom
			copy(s.stack, tt.values)

			result := s.CurrentSize()
			if result != tt.expected {
				t.Errorf("CurrentSize() = %d, expected %d", result, tt.expected)
			}
		})
	}
}

// TestNextUp tests the NextUp function (equivalent to next_up in C)
func TestNextUp(t *testing.T) {
	tests := []struct {
		name     string
		capacity int
		values   []int
		top      int
		bottom   int
		index    int
		expected int
	}{
		{
			name:     "normal_case",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			index:    2,
			expected: 1,
		},
		{
			name:     "wrap_around",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			index:    0,
			expected: 4,
		},
		{
			name:     "empty_stack",
			capacity: 5,
			values:   []int{0, 0, 0, 0, 0},
			top:      0,
			bottom:   0,
			index:    3,
			expected: 3,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			s := New()
			s.InitWithCapacity(tt.capacity)
			s.top = tt.top
			s.bottom = tt.bottom
			copy(s.stack, tt.values)

			result := s.NextUp(tt.index)
			if result != tt.expected {
				t.Errorf("NextUp(%d) = %d, expected %d", tt.index, result, tt.expected)
			}
		})
	}
}

// TestNextDown tests the NextDown function (equivalent to next_down in C)
func TestNextDown(t *testing.T) {
	tests := []struct {
		name     string
		capacity int
		values   []int
		top      int
		bottom   int
		index    int
		expected int
	}{
		{
			name:     "normal_case",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			index:    2,
			expected: 3,
		},
		{
			name:     "wrap_around",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			index:    4,
			expected: 0,
		},
		{
			name:     "empty_stack",
			capacity: 5,
			values:   []int{0, 0, 0, 0, 0},
			top:      0,
			bottom:   0,
			index:    3,
			expected: 3,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			s := New()
			s.InitWithCapacity(tt.capacity)
			s.top = tt.top
			s.bottom = tt.bottom
			copy(s.stack, tt.values)

			result := s.NextDown(tt.index)
			if result != tt.expected {
				t.Errorf("NextDown(%d) = %d, expected %d", tt.index, result, tt.expected)
			}
		})
	}
}

// TestGetValueAtPosition tests the GetValueAtPosition function (equivalent to value in C)
func TestGetValueAtPosition(t *testing.T) {
	tests := []struct {
		name     string
		capacity int
		values   []int
		top      int
		bottom   int
		position int
		expected int
	}{
		{
			name:     "first_element",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			position: 1,
			expected: 1,
		},
		{
			name:     "third_element",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			position: 3,
			expected: 3,
		},
		{
			name:     "last_element",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			position: 5,
			expected: 5,
		},
		{
			name:     "wrapped_stack",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      3,
			bottom:   2,
			position: 2,
			expected: 5,
		},
		{
			name:     "invalid_position_zero",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      4,
			bottom:   0,
			position: 0,
			expected: 5, // C implementation returns 5 (undefined behavior)
		},
		{
			name:     "position_beyond_size",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      4,
			bottom:   0,
			position: 10,
			expected: 4, // C implementation returns 4 (undefined behavior)
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			s := New()
			s.InitWithCapacity(tt.capacity)
			s.top = tt.top
			s.bottom = tt.bottom
			copy(s.stack, tt.values)

			result := s.GetValueAtPosition(tt.position)
			if result != tt.expected {
				t.Errorf("GetValueAtPosition(%d) = %d, expected %d", tt.position, result, tt.expected)
			}
		})
	}
}

// TestIsFull tests the IsFull function (equivalent to is_full in C)
func TestIsFull(t *testing.T) {
	tests := []struct {
		name     string
		capacity int
		values   []int
		top      int
		bottom   int
		expected bool
	}{
		{
			name:     "true_case",
			capacity: 5,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			expected: true,
		},
		{
			name:     "false_case",
			capacity: 10,
			values:   []int{1, 2, 3, 4, 5},
			top:      0,
			bottom:   4,
			expected: false,
		},
		{
			name:     "empty_stack",
			capacity: 5,
			values:   []int{0, 0, 0, 0, 0},
			top:      0,
			bottom:   0,
			expected: false,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			s := New()
			s.InitWithCapacity(tt.capacity)
			s.top = tt.top
			s.bottom = tt.bottom
			copy(s.stack, tt.values)

			result := s.IsFull()
			if result != tt.expected {
				t.Errorf("IsFull() = %v, expected %v", result, tt.expected)
			}
		})
	}
}

// TestConsistency tests that multiple calls to the same function return consistent results
func TestConsistency(t *testing.T) {
	t.Run("current_size_multiple_calls", func(t *testing.T) {
		s := New()
		s.InitWithCapacity(5)
		s.FillFromSlice([]int{1, 2, 3, 4, 5})

		call1 := s.CurrentSize()
		call2 := s.CurrentSize()
		call3 := s.CurrentSize()

		if call1 != call2 || call2 != call3 {
			t.Errorf("Inconsistent CurrentSize() calls: %d, %d, %d", call1, call2, call3)
		}
	})

	t.Run("next_up_multiple_calls", func(t *testing.T) {
		s := New()
		s.InitWithCapacity(5)
		s.FillFromSlice([]int{1, 2, 3, 4, 5})

		call1 := s.NextUp(2)
		call2 := s.NextUp(2)
		call3 := s.NextUp(2)

		if call1 != call2 || call2 != call3 {
			t.Errorf("Inconsistent NextUp(2) calls: %d, %d, %d", call1, call2, call3)
		}
	})
}


