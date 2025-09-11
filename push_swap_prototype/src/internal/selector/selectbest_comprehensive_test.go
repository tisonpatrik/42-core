package selector

import (
	"testing"

	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// TestSelectBestBtoAMove_AllCombinations_1_2_3_4 tests all combinations of [1,2,3,4]
func TestSelectBestBtoAMove_AllCombinations_1_2_3_4(t *testing.T) {
	// All permutations of [1,2,3,4]
	permutations := [][]int{
		{1, 2, 3, 4}, {1, 2, 4, 3}, {1, 3, 2, 4}, {1, 3, 4, 2}, {1, 4, 2, 3}, {1, 4, 3, 2},
		{2, 1, 3, 4}, {2, 1, 4, 3}, {2, 3, 1, 4}, {2, 3, 4, 1}, {2, 4, 1, 3}, {2, 4, 3, 1},
		{3, 1, 2, 4}, {3, 1, 4, 2}, {3, 2, 1, 4}, {3, 2, 4, 1}, {3, 4, 1, 2}, {3, 4, 2, 1},
		{4, 1, 2, 3}, {4, 1, 3, 2}, {4, 2, 1, 3}, {4, 2, 3, 1}, {4, 3, 1, 2}, {4, 3, 2, 1},
	}
	
	for _, perm := range permutations {
		for splitPoint := 1; splitPoint < 4; splitPoint++ {
			stackA := perm[:splitPoint]
			stackB := perm[splitPoint:]
			
			// Arrange
			ps := &ops.SortingState{A: stack.InitStack(), B: stack.InitStack()}
			stack.FillStack(ps.A, stackA)
			stack.FillStack(ps.B, stackB)
			
			// Act
			result := SelectBestBtoAMove(ps, 30)
			
			// Assert
			if result.FromIndex < 0 || result.FromIndex >= len(stackB) {
				t.Errorf("FromIndex %d invalid for B %v", result.FromIndex, stackB)
			}
			if result.ToIndex < 0 || result.ToIndex > len(stackA) {
				t.Errorf("ToIndex %d invalid for A %v", result.ToIndex, stackA)
			}
			if result.Total < 0 {
				t.Errorf("Total cost %d should not be negative", result.Total)
			}
		}
	}
}


