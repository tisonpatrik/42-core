package solver

import "testing"

func TestComputeCost(t *testing.T) {
	tests := []struct {
		name     string
		posA     int
		sizeA    int
		posB     int
		sizeB    int
		expectedCost int
		expectedType string
	}{
		{
			name:         "Empty stacks",
			posA:         0,
			sizeA:        0,
			posB:         0,
			sizeB:        0,
			expectedCost: 0,
			expectedType: "",
		},
		{
			name:         "RR case - both positions at top",
			posA:         0,
			sizeA:        5,
			posB:         0,
			sizeB:        3,
			expectedCost: 0,
			expectedType: "rr",
		},
		{
			name:         "RR case - different positions",
			posA:         2,
			sizeA:        5,
			posB:         1,
			sizeB:        3,
			expectedCost: 2,
			expectedType: "rr",
		},
		{
			name:         "RRR case - both positions near bottom",
			posA:         4,
			sizeA:        5,
			posB:         2,
			sizeB:        3,
			expectedCost: 1,
			expectedType: "rrr",
		},
		{
			name:         "RA_RRB case - A near top, B near bottom",
			posA:         1,
			sizeA:        5,
			posB:         2,
			sizeB:        3,
			expectedCost: 2,
			expectedType: "rr", // This is actually RR case since posA=1, posB=2
		},
		{
			name:         "RRA_RB case - A near bottom, B near top",
			posA:         4,
			sizeA:        5,
			posB:         1,
			sizeB:        3,
			expectedCost: 2,
			expectedType: "rrr", // This is actually RRR case since sizeA-posA=1, sizeB-posB=2
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			cost, typ := computeCost(tt.posA, tt.sizeA, tt.posB, tt.sizeB)
			
			if cost != tt.expectedCost {
				t.Errorf("computeCost(%d, %d, %d, %d) cost = %d, want %d", 
					tt.posA, tt.sizeA, tt.posB, tt.sizeB, cost, tt.expectedCost)
			}
			
			if typ != tt.expectedType {
				t.Errorf("computeCost(%d, %d, %d, %d) type = %s, want %s", 
					tt.posA, tt.sizeA, tt.posB, tt.sizeB, typ, tt.expectedType)
			}
		})
	}
}

func TestMax(t *testing.T) {
	tests := []struct {
		name     string
		a        int
		b        int
		expected int
	}{
		{"Positive numbers", 5, 3, 5},
		{"Negative numbers", -5, -3, -3},
		{"Mixed numbers", 5, -3, 5},
		{"Equal numbers", 5, 5, 5},
		{"Zero", 0, 5, 5},
		{"Zero", 5, 0, 5},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := max(tt.a, tt.b)
			if result != tt.expected {
				t.Errorf("max(%d, %d) = %d, want %d", tt.a, tt.b, result, tt.expected)
			}
		})
	}
}

func TestComputeCostEdgeCases(t *testing.T) {
	t.Run("Large positions", func(t *testing.T) {
		cost, typ := computeCost(1000, 1001, 500, 501)
		if cost < 0 {
			t.Error("Cost should be non-negative")
		}
		if typ == "" {
			t.Error("Type should not be empty for valid inputs")
		}
	})
	
	t.Run("Boundary positions", func(t *testing.T) {
		// Test at boundaries of stack sizes
		cost, _ := computeCost(0, 1, 0, 1)
		if cost != 0 {
			t.Errorf("Boundary case cost = %d, want 0", cost)
		}
	})
}
