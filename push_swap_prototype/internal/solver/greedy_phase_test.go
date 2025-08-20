package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

func TestProcessGreedyPhase(t *testing.T) {
	t.Run("Empty stack B", func(t *testing.T) {
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice([]int{1, 2, 3})
		
		result := ProcessGreedyPhase(stacks)
		
		if len(result) != 0 {
			t.Errorf("Expected no operations for empty stack B, got %v", result)
		}
	})
	
	t.Run("Single element in stack B", func(t *testing.T) {
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice([]int{1, 3, 5})
		
		// Move some elements to B
		stacks.PB() // Move 5 to B
		stacks.PB() // Move 3 to B
		
		result := ProcessGreedyPhase(stacks)
		
		// Should have operations to move elements back
		if len(result) == 0 {
			t.Error("Expected operations to move elements back from B")
		}
		
		// Verify stack B is empty after processing
		if !stacks.B.IsEmpty() {
			t.Error("Stack B should be empty after greedy phase")
		}
	})
	
	t.Run("Multiple elements in stack B", func(t *testing.T) {
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice([]int{1, 4, 7})
		
		// Move elements to B
		stacks.PB() // Move 7 to B
		stacks.PB() // Move 4 to B
		
		result := ProcessGreedyPhase(stacks)
		
		// Should have operations to move elements back
		if len(result) == 0 {
			t.Error("Expected operations to move elements back from B")
		}
		
		// Verify stack B is empty after processing
		if !stacks.B.IsEmpty() {
			t.Error("Stack B should be empty after greedy phase")
		}
	})
}

func TestFindBestMove(t *testing.T) {
	t.Run("Find best move for simple case", func(t *testing.T) {
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice([]int{1, 3, 5})
		
		// Move an element to B
		stacks.PB() // Move 5 to B
		
		bestMove := findBestMove(stacks)
		
		if bestMove.posA < 0 || bestMove.posB < 0 {
			t.Error("Best move should have valid positions")
		}
		
		if bestMove.typ == "" {
			t.Error("Best move should have a valid type")
		}
		
		if bestMove.cost < 0 {
			t.Error("Best move should have a non-negative cost")
		}
	})
	
	t.Run("Find best move for multiple elements", func(t *testing.T) {
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice([]int{1, 3, 5, 7, 9})
		
		// Move multiple elements to B
		stacks.PB() // Move 9 to B
		stacks.PB() // Move 7 to B
		stacks.PB() // Move 5 to B
		
		bestMove := findBestMove(stacks)
		
		if bestMove.posA < 0 || bestMove.posB < 0 {
			t.Error("Best move should have valid positions")
		}
		
		if bestMove.typ == "" {
			t.Error("Best move should have a valid type")
		}
		
		if bestMove.cost < 0 {
			t.Error("Best move should have a non-negative cost")
		}
	})
}

func TestGreedyPhaseIntegration(t *testing.T) {
	t.Run("Complete greedy phase workflow", func(t *testing.T) {
		stacks := operations.NewPushSwapStacks()
		stacks.InitializeFromSlice([]int{1, 3, 5, 7, 9})
		
		// Move some elements to B
		stacks.PB() // Move 9 to B
		stacks.PB() // Move 7 to B
		
		initialSizeA := stacks.A.Size()
		initialSizeB := stacks.B.Size()
		
		result := ProcessGreedyPhase(stacks)
		
		// Verify all elements moved back
		finalSizeA := stacks.A.Size()
		finalSizeB := stacks.B.Size()
		
		if finalSizeA != initialSizeA+initialSizeB {
			t.Errorf("Expected stack A to have %d elements, got %d", 
				initialSizeA+initialSizeB, finalSizeA)
		}
		
		if finalSizeB != 0 {
			t.Errorf("Expected stack B to be empty, got %d elements", finalSizeB)
		}
		
		// Should have operations
		if len(result) == 0 {
			t.Error("Expected operations from greedy phase")
		}
	})
}
