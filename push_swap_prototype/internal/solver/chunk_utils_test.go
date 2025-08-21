package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

// TestLocToStack tests the locToStack function with different locations
func TestLocToStack(t *testing.T) {
	ps := operations.NewPushSwapData()
	
	// Test TOP_A
	stk := locToStack(ps, operations.TOP_A)
	if stk != ps.A {
		t.Error("TOP_A should return stack A")
	}
	
	// Test BOTTOM_A
	stk = locToStack(ps, operations.BOTTOM_A)
	if stk != ps.A {
		t.Error("BOTTOM_A should return stack A")
	}
	
	// Test TOP_B
	stk = locToStack(ps, operations.TOP_B)
	if stk != ps.B {
		t.Error("TOP_B should return stack B")
	}
	
	// Test BOTTOM_B
	stk = locToStack(ps, operations.BOTTOM_B)
	if stk != ps.B {
		t.Error("BOTTOM_B should return stack B")
	}
}

// TestChunkValueTopA tests chunkValue for TOP_A location
func TestChunkValueTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 3}
	
	// Test position 1 (should be first element)
	val := chunkValue(ps, chunk, 1)
	if val != 1 {
		t.Errorf("Expected value 1 at position 1, got %d", val)
	}
	
	// Test position 2 (should be second element)
	val = chunkValue(ps, chunk, 2)
	if val != 2 {
		t.Errorf("Expected value 2 at position 2, got %d", val)
	}
	
	// Test position 3 (should be third element)
	val = chunkValue(ps, chunk, 3)
	if val != 3 {
		t.Errorf("Expected value 3 at position 3, got %d", val)
	}
	
	// Test out of bounds position
	val = chunkValue(ps, chunk, 4)
	if val != 0 {
		t.Errorf("Expected value 0 for out of bounds position, got %d", val)
	}
}

// TestChunkValueBottomA tests chunkValue for BOTTOM_A location
func TestChunkValueBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	
	// Test position 1 (should be last element)
	val := chunkValue(ps, chunk, 1)
	if val != 5 {
		t.Errorf("Expected value 5 at position 1, got %d", val)
	}
	
	// Test position 2 (should be second-to-last element)
	val = chunkValue(ps, chunk, 2)
	if val != 4 {
		t.Errorf("Expected value 4 at position 2, got %d", val)
	}
	
	// Test position 3 (should be third-to-last element)
	val = chunkValue(ps, chunk, 3)
	if val != 3 {
		t.Errorf("Expected value 3 at position 3, got %d", val)
	}
}

// TestChunkValueTopB tests chunkValue for TOP_B location
func TestChunkValueTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{10, 20, 30})
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 2}
	
	// Test position 1 (should be first element)
	val := chunkValue(ps, chunk, 1)
	if val != 10 {
		t.Errorf("Expected value 10 at position 1, got %d", val)
	}
	
	// Test position 2 (should be second element)
	val = chunkValue(ps, chunk, 2)
	if val != 20 {
		t.Errorf("Expected value 20 at position 2, got %d", val)
	}
}

// TestChunkValueBottomB tests chunkValue for BOTTOM_B location
func TestChunkValueBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{10, 20, 30})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 2}
	
	// Test position 1 (should be last element)
	val := chunkValue(ps, chunk, 1)
	if val != 30 {
		t.Errorf("Expected value 30 at position 1, got %d", val)
	}
	
	// Test position 2 (should be second-to-last element)
	val = chunkValue(ps, chunk, 2)
	if val != 20 {
		t.Errorf("Expected value 20 at position 2, got %d", val)
	}
}

// TestChunkValueEmptyStack tests chunkValue with empty stacks
func TestChunkValueEmptyStack(t *testing.T) {
	ps := operations.NewPushSwapData()
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 1}
	
	// Test with empty stack
	val := chunkValue(ps, chunk, 1)
	if val != 0 {
		t.Errorf("Expected value 0 for empty stack, got %d", val)
	}
}

// TestChunkMaxValueTopA tests chunkMaxValue for TOP_A location
func TestChunkMaxValueTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{5, 2, 8, 1, 3})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 3}
	
	maxVal := chunkMaxValue(ps, chunk)
	if maxVal != 8 {
		t.Errorf("Expected max value 8, got %d", maxVal)
	}
}

// TestChunkMaxValueBottomA tests chunkMaxValue for BOTTOM_A location
func TestChunkMaxValueBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{1, 2, 3, 9, 4})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	
	maxVal := chunkMaxValue(ps, chunk)
	if maxVal != 9 {
		t.Errorf("Expected max value 9, got %d", maxVal)
	}
}

// TestChunkMaxValueTopB tests chunkMaxValue for TOP_B location
func TestChunkMaxValueTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{15, 7, 22, 3})
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 2}
	
	maxVal := chunkMaxValue(ps, chunk)
	if maxVal != 15 {
		t.Errorf("Expected max value 15, got %d", maxVal)
	}
}

// TestChunkMaxValueBottomB tests chunkMaxValue for BOTTOM_B location
func TestChunkMaxValueBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{3, 7, 15, 22})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 2}
	
	maxVal := chunkMaxValue(ps, chunk)
	if maxVal != 22 {
		t.Errorf("Expected max value 22, got %d", maxVal)
	}
}

// TestChunkMaxValueSingleElement tests chunkMaxValue with single element
func TestChunkMaxValueSingleElement(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(2)
	ps.A.FillFromSlice([]int{42})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 1}
	
	maxVal := chunkMaxValue(ps, chunk)
	if maxVal != 42 {
		t.Errorf("Expected max value 42, got %d", maxVal)
	}
}

// TestChunkMaxValueEmptyChunk tests chunkMaxValue with empty chunk
func TestChunkMaxValueEmptyChunk(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(2)
	ps.A.FillFromSlice([]int{1, 2})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 0}
	
	maxVal := chunkMaxValue(ps, chunk)
	if maxVal != 0 {
		t.Errorf("Expected max value 0 for empty chunk, got %d", maxVal)
	}
}

// TestAPartlySort tests aPartlySort function
func TestAPartlySort(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	
	// Test with sorted stack
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5})
	if !aPartlySort(ps, 1) {
		t.Error("Sorted stack should be partly sorted from position 1")
	}
	
	// Test with unsorted stack
	ps.A.FillFromSlice([]int{1, 3, 2, 4, 5})
	if aPartlySort(ps, 1) {
		t.Error("Unsorted stack should not be partly sorted from position 1")
	}
	
	// Test with partial sorting from position 2
	ps.A.FillFromSlice([]int{5, 1, 2, 3, 4})
	if !aPartlySort(ps, 2) {
		t.Error("Stack should be partly sorted from position 2")
	}
}

// TestIsConsecutive tests isConsecutive function
func TestIsConsecutive(t *testing.T) {
	// Test consecutive numbers
	if !isConsecutive(1, 2, 3, 4) {
		t.Error("1,2,3,4 should be consecutive")
	}
	
	// Test non-consecutive numbers
	if isConsecutive(1, 2, 4, 5) {
		t.Error("1,2,4,5 should not be consecutive")
	}
	
	// Test with different order
	if !isConsecutive(4, 2, 1, 3) {
		t.Error("4,2,1,3 should be consecutive after sorting")
	}
}

// TestSortThreeNumbers tests sortThreeNumbers function
func TestSortThreeNumbers(t *testing.T) {
	a, b, c := 3, 1, 2
	
	sortThreeNumbers(&a, &b, &c)
	
	if a != 1 || b != 2 || c != 3 {
		t.Errorf("Expected sorted values 1,2,3, got %d,%d,%d", a, b, c)
	}
	
	// Test with already sorted numbers
	a, b, c = 1, 2, 3
	sortThreeNumbers(&a, &b, &c)
	if a != 1 || b != 2 || c != 3 {
		t.Errorf("Already sorted values should remain unchanged, got %d,%d,%d", a, b, c)
	}
	
	// Test with reverse order
	a, b, c = 3, 2, 1
	sortThreeNumbers(&a, &b, &c)
	if a != 1 || b != 2 || c != 3 {
		t.Errorf("Expected sorted values 1,2,3, got %d,%d,%d", a, b, c)
	}
}

// TestSortFourNumbers tests sortFourNumbers function
func TestSortFourNumbers(t *testing.T) {
	a, b, c, d := 4, 2, 1, 3
	
	sortFourNumbers(&a, &b, &c, &d)
	
	if a != 1 || b != 2 || c != 3 || d != 4 {
		t.Errorf("Expected sorted values 1,2,3,4, got %d,%d,%d,%d", a, b, c, d)
	}
	
	// Test with already sorted numbers
	a, b, c, d = 1, 2, 3, 4
	sortFourNumbers(&a, &b, &c, &d)
	if a != 1 || b != 2 || c != 3 || d != 4 {
		t.Errorf("Already sorted values should remain unchanged, got %d,%d,%d,%d", a, b, c, d)
	}
	
	// Test with reverse order
	a, b, c, d = 4, 3, 2, 1
	sortFourNumbers(&a, &b, &c, &d)
	if a != 1 || b != 2 || c != 3 || d != 4 {
		t.Errorf("Expected sorted values 1,2,3,4, got %d,%d,%d,%d", a, b, c, d)
	}
	
	// Test with mixed order
	a, b, c, d = 3, 1, 4, 2
	sortFourNumbers(&a, &b, &c, &d)
	if a != 1 || b != 2 || c != 3 || d != 4 {
		t.Errorf("Expected sorted values 1,2,3,4, got %d,%d,%d,%d", a, b, c, d)
	}
}

// TestChunkValueEdgeCases tests edge cases for chunkValue
func TestChunkValueEdgeCases(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{10, 20, 30})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 3}
	
	// Test position 0 (invalid, should return 0)
	val := chunkValue(ps, chunk, 0)
	if val != 0 {
		t.Errorf("Expected value 0 for invalid position 0, got %d", val)
	}
	
	// Test negative position (invalid, should return 0)
	val = chunkValue(ps, chunk, -1)
	if val != 0 {
		t.Errorf("Expected value 0 for invalid position -1, got %d", val)
	}
	
	// Test position larger than chunk size
	val = chunkValue(ps, chunk, 5)
	if val != 0 {
		t.Errorf("Expected value 0 for position larger than chunk size, got %d", val)
	}
}

// TestChunkValueMixedLocations tests chunkValue with different locations
func TestChunkValueMixedLocations(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{1, 2, 3, 4})
	ps.B.FillFromSlice([]int{10, 20, 30, 40})
	
	// Test TOP_A
	chunkA := &operations.Chunk{Loc: operations.TOP_A, Size: 2}
	val := chunkValue(ps, chunkA, 1)
	if val != 1 {
		t.Errorf("TOP_A position 1 should be 1, got %d", val)
	}
	
	// Test TOP_B
	chunkB := &operations.Chunk{Loc: operations.TOP_B, Size: 2}
	val = chunkValue(ps, chunkB, 1)
	if val != 10 {
		t.Errorf("TOP_B position 1 should be 10, got %d", val)
	}
	
	// Test BOTTOM_A
	chunkBottomA := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 2}
	val = chunkValue(ps, chunkBottomA, 1)
	if val != 4 {
		t.Errorf("BOTTOM_A position 1 should be 4, got %d", val)
	}
	
	// Test BOTTOM_B
	chunkBottomB := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 2}
	val = chunkValue(ps, chunkBottomB, 1)
	if val != 40 {
		t.Errorf("BOTTOM_B position 1 should be 40, got %d", val)
	}
}
