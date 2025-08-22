package solver

import (
	"push_swap_prototype/internal/stack"
	"testing"
)

func TestChunkMaxValue(t *testing.T) {
	tests := []struct {
		name     string
		setupA   []int
		setupB   []int
		topA     int
		bottomA  int
		topB     int
		bottomB  int
		chunk    stack.Chunk
		expected int
	}{
		{
			name:     "chunk_max_value_top_a_normal",
			setupA:   []int{10, 25, 15, 30, 5},
			setupB:   []int{0, 0, 0, 0, 0},
			topA:     0,
			bottomA:  4,
			topB:     0,
			bottomB:  0,
			chunk:    stack.Chunk{Loc: stack.TOP_A, Size: 3},
			expected: 25,
		},
		{
			name:     "chunk_max_value_top_b_normal",
			setupA:   []int{0, 0, 0, 0, 0},
			setupB:   []int{42, 18, 33, 7, 55},
			topA:     0,
			bottomA:  0,
			topB:     0,
			bottomB:  4,
			chunk:    stack.Chunk{Loc: stack.TOP_B, Size: 4},
			expected: 42,
		},
		{
			name:     "chunk_max_value_bottom_a_normal",
			setupA:   []int{20, 35, 12, 28, 45},
			setupB:   []int{0, 0, 0, 0, 0},
			topA:     0,
			bottomA:  4,
			topB:     0,
			bottomB:  0,
			chunk:    stack.Chunk{Loc: stack.BOTTOM_A, Size: 2},
			expected: 45,
		},
		{
			name:     "chunk_max_value_bottom_b_normal",
			setupA:   []int{0, 0, 0, 0, 0},
			setupB:   []int{8, 22, 17, 31, 14},
			topA:     0,
			bottomA:  0,
			topB:     0,
			bottomB:  4,
			chunk:    stack.Chunk{Loc: stack.BOTTOM_B, Size: 3},
			expected: 31,
		},
		{
			name:     "chunk_max_value_single_element",
			setupA:   []int{10, 25, 15, 30, 5},
			setupB:   []int{0, 0, 0, 0, 0},
			topA:     0,
			bottomA:  4,
			topB:     0,
			bottomB:  0,
			chunk:    stack.Chunk{Loc: stack.TOP_A, Size: 1},
			expected: 10,
		},
		{
			name:     "chunk_max_value_full_stack",
			setupA:   []int{10, 25, 15, 30, 5},
			setupB:   []int{0, 0, 0, 0, 0},
			topA:     0,
			bottomA:  4,
			topB:     0,
			bottomB:  0,
			chunk:    stack.Chunk{Loc: stack.TOP_A, Size: 5},
			expected: 30,
		},
		{
			name:     "chunk_max_value_wrapped_stack",
			setupA:   []int{50, 60, 70, 80, 90},
			setupB:   []int{0, 0, 0, 0, 0},
			topA:     3,
			bottomA:  2,
			topB:     0,
			bottomB:  0,
			chunk:    stack.Chunk{Loc: stack.TOP_A, Size: 3},
			expected: 90,
		},
		{
			name:     "chunk_max_value_oversized_chunk",
			setupA:   []int{10, 25, 15, 30, 5},
			setupB:   []int{0, 0, 0, 0, 0},
			topA:     0,
			bottomA:  4,
			topB:     0,
			bottomB:  0,
			chunk:    stack.Chunk{Loc: stack.TOP_A, Size: 10},
			expected: 30,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			// Arrange
			ps := stack.NewPushSwapData()
			
					// Setup stack A
		if len(tt.setupA) > 0 {
			ps.A = stack.FromSlice(tt.setupA)
			ps.A.SetTop(tt.topA)
			ps.A.SetBottom(tt.bottomA)
		}
		
		// Setup stack B
		if len(tt.setupB) > 0 {
			ps.B = stack.FromSlice(tt.setupB)
			ps.B.SetTop(tt.topB)
			ps.B.SetBottom(tt.bottomB)
		}

			// Act
			result := chunkMaxValue(ps, &tt.chunk)

			// Assert
			if result != tt.expected {
				t.Errorf("chunkMaxValue() = %d, want %d", result, tt.expected)
			}
		})
	}
}

func TestChunkMaxValueConsistency(t *testing.T) {
	// Arrange
	ps := stack.NewPushSwapData()
	ps.A = stack.FromSlice([]int{10, 25, 15, 30, 5})
	ps.A.SetTop(0)
	ps.A.SetBottom(4)
	chunk := stack.Chunk{Loc: stack.TOP_A, Size: 3}

	// Act
	result1 := chunkMaxValue(ps, &chunk)
	result2 := chunkMaxValue(ps, &chunk)
	result3 := chunkMaxValue(ps, &chunk)

	// Assert
	if result1 != result2 || result2 != result3 {
		t.Errorf("Consistency failed: call1=%d, call2=%d, call3=%d", result1, result2, result3)
	}
	
	// Verify all calls return the expected value
	expected := 25
	if result1 != expected {
		t.Errorf("Expected %d, got %d", expected, result1)
	}
}
