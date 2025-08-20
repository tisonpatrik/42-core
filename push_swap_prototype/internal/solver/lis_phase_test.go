package solver

import (
	"push_swap_prototype/internal/operations"
	"reflect"
	"testing"
)

func TestProcessLISPhase(t *testing.T) {
	tests := []struct {
		name     string
		input    []int
		expected []string
	}{
		{
			name:     "Empty array",
			input:    []int{},
			expected: []string{},
		},
		{
			name:     "Single element",
			input:    []int{5},
			expected: []string{"ra"}, // Keep in A, rotate
		},
		{
			name:     "Already sorted",
			input:    []int{1, 2, 3, 4, 5},
			expected: []string{"ra", "ra", "ra", "ra", "ra"}, // All kept in A
		},
		{
			name:     "Reverse sorted",
			input:    []int{5, 4, 3, 2, 1},
			expected: []string{"ra", "pb", "pb", "pb", "pb"}, // Only 5 kept in A
		},
		{
			name:     "Mixed array",
			input:    []int{3, 1, 4, 1, 5, 9, 2, 6},
			expected: []string{"ra", "pb", "ra", "pb", "ra", "ra", "pb", "ra"},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			stacks := operations.NewPushSwapStacks()
			result := ProcessLISPhase(tt.input, stacks)
			
			if !reflect.DeepEqual(result, tt.expected) {
				t.Errorf("ProcessLISPhase(%v) = %v, want %v", 
					tt.input, result, tt.expected)
			}
		})
	}
}

func TestProcessLISPhaseStackState(t *testing.T) {
	t.Run("Verify stack state after LIS phase", func(t *testing.T) {
		input := []int{3, 1, 4, 1, 5, 9, 2, 6}
		stacks := operations.NewPushSwapStacks()
		
		ProcessLISPhase(input, stacks)
		
		// Verify stack A contains LIS elements
		stackA := stacks.GetStackASlice()
		if len(stackA) == 0 {
			t.Error("Stack A should not be empty after LIS phase")
		}
		
		// Verify stack B contains non-LIS elements
		stackB := stacks.GetStackBSlice()
		if len(stackB) == 0 {
			t.Error("Stack B should contain non-LIS elements")
		}
		
		// Verify total elements preserved
		totalElements := len(stackA) + len(stackB)
		if totalElements != len(input) {
			t.Errorf("Total elements mismatch: got %d, want %d", totalElements, len(input))
		}
	})
}
