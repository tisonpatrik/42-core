package solver

import (
	"push_swap_prototype/internal/operations"
	"reflect"
	"testing"
)

func TestProcessFinalPhase(t *testing.T) {
	tests := []struct {
		name     string
		input    []int
		expected []string
	}{
		{
			name:     "Empty stack",
			input:    []int{},
			expected: []string{},
		},
		{
			name:     "Single element",
			input:    []int{5},
			expected: []string{},
		},
		{
			name:     "Minimum at top",
			input:    []int{1, 2, 3, 4, 5},
			expected: []string{},
		},
		{
			name:     "Minimum in middle - rotate up",
			input:    []int{3, 4, 1, 5, 2},
			expected: []string{"ra", "ra"},
		},
		{
			name:     "Minimum near bottom - rotate down",
			input:    []int{4, 5, 2, 3, 1},
			expected: []string{"rra"},
		},
		{
			name:     "Minimum at bottom - rotate down",
			input:    []int{5, 4, 3, 2, 1},
			expected: []string{"rra"}, // Only 1 rra needed: 5-4 = 1
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			stacks := operations.NewPushSwapStacks()
			stacks.InitializeFromSlice(tt.input)
			
			result := ProcessFinalPhase(stacks)
			
			if !reflect.DeepEqual(result, tt.expected) {
				t.Errorf("ProcessFinalPhase(%v) = %v, want %v", 
					tt.input, result, tt.expected)
			}
		})
	}
}

func TestProcessFinalPhaseStackState(t *testing.T) {
	t.Run("Verify minimum is at top after final phase", func(t *testing.T) {
		input := []int{4, 5, 2, 3, 1}
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice(input)
		
		ProcessFinalPhase(stacks)
		
		// Verify minimum is at top
		stackA := stacks.GetStackASlice()
		if len(stackA) == 0 {
			t.Error("Stack A should not be empty after final phase")
		}
		
		// Check if minimum is at top
		minVal := stackA[0]
		for _, val := range stackA {
			if val < minVal {
				t.Errorf("Minimum value %d is not at top, found smaller value %d", minVal, val)
			}
		}
	})
	
	t.Run("Verify operations are minimal", func(t *testing.T) {
		input := []int{5, 4, 3, 2, 1}
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice(input)
		
		// This should use rra operations (more efficient than multiple ra)
		result := ProcessFinalPhase(stacks)
		
		// Should use rra operations for efficiency
		expectedOps := []string{"rra"} // Only 1 rra needed
		if !reflect.DeepEqual(result, expectedOps) {
			t.Errorf("Expected efficient operations %v, got %v", expectedOps, result)
		}
	})
}
