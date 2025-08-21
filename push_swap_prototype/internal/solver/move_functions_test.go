package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

func TestMoveFromTo(t *testing.T) {
	tests := []struct {
		name     string
		from     operations.Loc
		to       operations.Loc
		expected int
	}{
		{"TOP_A to TOP_B", operations.TOP_A, operations.TOP_B, 1},
		{"TOP_A to BOTTOM_A", operations.TOP_A, operations.BOTTOM_A, 1},
		{"TOP_A to BOTTOM_B", operations.TOP_A, operations.BOTTOM_B, 1},
		{"TOP_B to TOP_A", operations.TOP_B, operations.TOP_A, 1},
		{"TOP_B to BOTTOM_B", operations.TOP_B, operations.BOTTOM_B, 1},
		{"TOP_B to BOTTOM_A", operations.TOP_B, operations.BOTTOM_A, 1},
		{"BOTTOM_A to TOP_A", operations.BOTTOM_A, operations.TOP_A, 1},
		{"BOTTOM_A to TOP_B", operations.BOTTOM_A, operations.TOP_B, 1},
		{"BOTTOM_A to BOTTOM_B", operations.BOTTOM_A, operations.BOTTOM_B, 1},
		{"BOTTOM_B to TOP_B", operations.BOTTOM_B, operations.TOP_B, 1},
		{"BOTTOM_B to TOP_A", operations.BOTTOM_B, operations.TOP_A, 1},
		{"BOTTOM_B to BOTTOM_A", operations.BOTTOM_B, operations.BOTTOM_A, 1},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ps := operations.NewPushSwapData()
			// Initialize stacks with some data
			ps.A.Push(1)
			ps.A.Push(2)
			ps.B.Push(3)
			ps.B.Push(4)
			
			result := moveFromTo(ps, tt.from, tt.to)
			if result != tt.expected {
				t.Errorf("moveFromTo() = %v, want %v", result, tt.expected)
			}
		})
	}
}

func TestMoveFromTopA(t *testing.T) {
	tests := []struct {
		name     string
		to       operations.Loc
		expectedOps []operations.Operation
	}{
		{
			"TOP_A to TOP_B",
			operations.TOP_B,
			[]operations.Operation{operations.PB},
		},
		{
			"TOP_A to BOTTOM_A",
			operations.BOTTOM_A,
			[]operations.Operation{operations.RA},
		},
		{
			"TOP_A to BOTTOM_B",
			operations.BOTTOM_B,
			[]operations.Operation{operations.PB, operations.RB},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ps := operations.NewPushSwapData()
			// Initialize stack A with some data
			ps.A.Push(1)
			ps.A.Push(2)
			ps.A.Push(3)
			
			// Clear operation list
			ps.OpList = []operations.Operation{}
			
			moveFromTopA(ps, tt.to)
			
			if len(ps.OpList) != len(tt.expectedOps) {
				t.Errorf("Expected %d operations, got %d", len(tt.expectedOps), len(ps.OpList))
				return
			}
			
			for i, op := range tt.expectedOps {
				if ps.OpList[i] != op {
					t.Errorf("Operation %d: expected %v, got %v", i, op, ps.OpList[i])
				}
			}
		})
	}
}

func TestMoveFromTopB(t *testing.T) {
	tests := []struct {
		name     string
		to       operations.Loc
		expectedOps []operations.Operation
	}{
		{
			"TOP_B to TOP_A",
			operations.TOP_A,
			[]operations.Operation{operations.PA},
		},
		{
			"TOP_B to BOTTOM_B",
			operations.BOTTOM_B,
			[]operations.Operation{operations.RB},
		},
		{
			"TOP_B to BOTTOM_A",
			operations.BOTTOM_A,
			[]operations.Operation{operations.PA, operations.RA},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ps := operations.NewPushSwapData()
			// Initialize stack B with some data
			ps.B.Push(1)
			ps.B.Push(2)
			ps.B.Push(3)
			
			// Clear operation list
			ps.OpList = []operations.Operation{}
			
			moveFromTopB(ps, tt.to)
			
			if len(ps.OpList) != len(tt.expectedOps) {
				t.Errorf("Expected %d operations, got %d", len(tt.expectedOps), len(ps.OpList))
				return
			}
			
			for i, op := range tt.expectedOps {
				if ps.OpList[i] != op {
					t.Errorf("Operation %d: expected %v, got %v", i, op, ps.OpList[i])
				}
			}
		})
	}
}

func TestMoveFromBottomA(t *testing.T) {
	tests := []struct {
		name     string
		to       operations.Loc
		expectedOps []operations.Operation
	}{
		{
			"BOTTOM_A to TOP_A",
			operations.TOP_A,
			[]operations.Operation{operations.RRA},
		},
		{
			"BOTTOM_A to TOP_B",
			operations.TOP_B,
			[]operations.Operation{operations.RRA, operations.PB},
		},
		{
			"BOTTOM_A to BOTTOM_B",
			operations.BOTTOM_B,
			[]operations.Operation{operations.RRA, operations.PB, operations.RB},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ps := operations.NewPushSwapData()
			// Initialize stack A with some data
			ps.A.Push(1)
			ps.A.Push(2)
			ps.A.Push(3)
			
			// Clear operation list
			ps.OpList = []operations.Operation{}
			
			moveFromBottomA(ps, tt.to)
			
			if len(ps.OpList) != len(tt.expectedOps) {
				t.Errorf("Expected %d operations, got %d", len(tt.expectedOps), len(ps.OpList))
				return
			}
			
			for i, op := range tt.expectedOps {
				if ps.OpList[i] != op {
					t.Errorf("Operation %d: expected %v, got %v", i, op, ps.OpList[i])
				}
			}
		})
	}
}

func TestMoveFromBottomB(t *testing.T) {
	tests := []struct {
		name     string
		to       operations.Loc
		expectedOps []operations.Operation
	}{
		{
			"BOTTOM_B to TOP_B",
			operations.TOP_B,
			[]operations.Operation{operations.RRB},
		},
		{
			"BOTTOM_B to TOP_A",
			operations.TOP_A,
			[]operations.Operation{operations.RRB, operations.PA},
		},
		{
			"BOTTOM_B to BOTTOM_A",
			operations.BOTTOM_A,
			[]operations.Operation{operations.RRB, operations.PA, operations.RA},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ps := operations.NewPushSwapData()
			// Initialize stack B with some data
			ps.B.Push(1)
			ps.B.Push(2)
			ps.B.Push(3)
			
			// Clear operation list
			ps.OpList = []operations.Operation{}
			
			moveFromBottomB(ps, tt.to)
			
			if len(ps.OpList) != len(tt.expectedOps) {
				t.Errorf("Expected %d operations, got %d", len(tt.expectedOps), len(ps.OpList))
				return
			}
			
			for i, op := range tt.expectedOps {
				if ps.OpList[i] != op {
					t.Errorf("Operation %d: expected %v, got %v", i, op, ps.OpList[i])
				}
			}
		})
	}
}

// Test to verify the bug I found: BOTTOM_A to BOTTOM_B should use rotate_b, not r_rotate_b
func TestMoveFromBottomAToBottomBBug(t *testing.T) {
	ps := operations.NewPushSwapData()
	ps.A.Push(1)
	ps.A.Push(2)
	ps.A.Push(3)
	
	ps.OpList = []operations.Operation{}
	
	moveFromBottomA(ps, operations.BOTTOM_B)
	
	// Check that the operations are correct
	expectedOps := []operations.Operation{operations.RRA, operations.PB, operations.RB}
	
	if len(ps.OpList) != len(expectedOps) {
		t.Errorf("Expected %d operations, got %d", len(expectedOps), len(ps.OpList))
		return
	}
	
	for i, op := range expectedOps {
		if ps.OpList[i] != op {
			t.Errorf("Operation %d: expected %v, got %v", i, op, ps.OpList[i])
		}
	}
}

// Test to verify stack state changes after operations
func TestMoveOperationsStackState(t *testing.T) {
	ps := operations.NewPushSwapData()
	
	// Initialize stacks
	ps.A.Push(3)
	ps.A.Push(2)
	ps.A.Push(1)
	ps.B.Push(6)
	ps.B.Push(5)
	ps.B.Push(4)
	
	// Test moving from TOP_A to TOP_B
	initialASize := ps.A.Size()
	initialBSize := ps.B.Size()
	
	moveFromTopA(ps, operations.TOP_B)
	
	// After push_b, stack A should have one less element, B should have one more
	if ps.A.Size() != initialASize-1 {
		t.Errorf("Stack A size after push_b: expected %d, got %d", initialASize-1, ps.A.Size())
	}
	if ps.B.Size() != initialBSize+1 {
		t.Errorf("Stack B size after push_b: expected %d, got %d", initialBSize+1, ps.B.Size())
	}
}
