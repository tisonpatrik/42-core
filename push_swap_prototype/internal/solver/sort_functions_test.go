package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

// TestSortOneTopA tests sortOne for TOP_A location
func TestSortOneTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{3, 1, 2})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 1}
	originalSize := chunk.Size
	
	sortOne(ps, chunk)
	
	// Size should decrease by 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Stack A should remain unchanged since we're already at TOP_A
	if ps.A.Size() != 3 {
		t.Errorf("Expected stack A to have 3 elements, got %d", ps.A.Size())
	}
}

// TestSortOneBottomA tests sortOne for BOTTOM_A location
func TestSortOneBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{3, 1, 2}) // 2 is at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 1}
	originalSize := chunk.Size
	
	sortOne(ps, chunk)
	
	// Size should decrease by 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Bottom element should be moved to top
	if ps.A.GetValueAtPosition(1) != 2 {
		t.Errorf("Expected value 2 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestSortOneTopB tests sortOne for TOP_B location
func TestSortOneTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.B.FillFromSlice([]int{3, 1, 2})
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 1}
	originalSize := chunk.Size
	
	sortOne(ps, chunk)
	
	// Size should decrease by 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Element should be moved from B to A
	if ps.A.Size() != 1 {
		t.Errorf("Expected stack A to have 1 element, got %d", ps.A.Size())
	}
	if ps.A.GetValueAtPosition(1) != 3 {
		t.Errorf("Expected value 3 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestSortOneBottomB tests sortOne for BOTTOM_B location
func TestSortOneBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.B.FillFromSlice([]int{3, 1, 2}) // 2 is at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 1}
	originalSize := chunk.Size
	
	sortOne(ps, chunk)
	
	// Size should decrease by 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Bottom element should be moved to top of B, then pushed to A
	if ps.A.Size() != 1 {
		t.Errorf("Expected stack A to have 1 element, got %d", ps.A.Size())
	}
	if ps.A.GetValueAtPosition(1) != 2 {
		t.Errorf("Expected value 2 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestSortTwoTopA tests sortTwo for TOP_A location
func TestSortTwoTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{3, 1, 2})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 2}
	originalSize := chunk.Size
	
	sortTwo(ps, chunk)
	
	// Size should decrease by 2
	if chunk.Size != originalSize-2 {
		t.Errorf("Expected size to decrease by 2, got %d", originalSize-chunk.Size)
	}
	
	// Elements should be sorted
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	if first > second {
		t.Errorf("Expected sorted order, got %d > %d", first, second)
	}
}

// TestSortTwoBottomA tests sortTwo for BOTTOM_A location
func TestSortTwoBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{3, 1, 2}) // 1, 2 are at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 2}
	originalSize := chunk.Size
	
	sortTwo(ps, chunk)
	
	// Size should decrease by 2
	if chunk.Size != originalSize-2 {
		t.Errorf("Expected size to decrease by 2, got %d", originalSize-chunk.Size)
	}
	
	// Elements should be moved to top and sorted
	if ps.A.Size() != 3 {
		t.Errorf("Expected stack A to have 3 elements, got %d", ps.A.Size())
	}
}

// TestSortTwoTopB tests sortTwo for TOP_B location
func TestSortTwoTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.B.FillFromSlice([]int{5, 3})
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 2}
	originalSize := chunk.Size
	
	sortTwo(ps, chunk)
	
	// Size should decrease by 2
	if chunk.Size != originalSize-2 {
		t.Errorf("Expected size to decrease by 2, got %d", originalSize-chunk.Size)
	}
	
	// Both elements should be moved to A
	if ps.A.Size() != 2 {
		t.Errorf("Expected stack A to have 2 elements, got %d", ps.A.Size())
	}
}

// TestSortTwoAlreadySorted tests sortTwo with already sorted elements
func TestSortTwoAlreadySorted(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{3, 5})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 2}
	originalSize := chunk.Size
	
	sortTwo(ps, chunk)
	
	// Size should decrease by 2
	if chunk.Size != originalSize-2 {
		t.Errorf("Expected size to decrease by 2, got %d", originalSize-chunk.Size)
	}
	
	// Elements should remain sorted
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	if first > second {
		t.Errorf("Expected sorted order, got %d > %d", first, second)
	}
}

// TestSortThreeTopA tests sortThree for TOP_A location
func TestSortThreeTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{3, 1, 2})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should remain the same (sortThree doesn't change size)
	if chunk.Size != originalSize {
		t.Errorf("Expected size to remain %d, got %d", originalSize, chunk.Size)
	}
	
	// Elements should be sorted
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	third := ps.A.GetValueAtPosition(3)
	if first > second || second > third {
		t.Errorf("Expected sorted order, got %d, %d, %d", first, second, third)
	}
}

// TestSortThreeTopB tests sortThree for TOP_B location
func TestSortThreeTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{3, 1, 2}) // Max value 3 is first
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomA tests sortThree for BOTTOM_A location
func TestSortThreeBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{5, 6, 3, 1, 2}) // 3, 1, 2 are at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomB tests sortThree for BOTTOM_B location
func TestSortThreeBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{5, 6, 3, 1, 2}) // 3, 1, 2 are at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeTopBMaxFirst tests sortThreeTopB when max value is first
func TestSortThreeTopBMaxFirst(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{3, 1, 2}) // Max value 3 is first
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeTopBMaxSecond tests sortThreeTopB when max value is second
func TestSortThreeTopBMaxSecond(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{1, 3, 2}) // Max value 3 is second
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeTopBMaxThird tests sortThreeTopB when max value is third
func TestSortThreeTopBMaxThird(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{1, 2, 3}) // Max value 3 is third
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomAMaxFirst tests sortThreeBottomA when max value is first
func TestSortThreeBottomAMaxFirst(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{5, 6, 3, 1, 2}) // Max value 3 is first of bottom 3
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomAMaxSecond tests sortThreeBottomA when max value is second
func TestSortThreeBottomAMaxSecond(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{5, 6, 1, 3, 2}) // Max value 3 is second of bottom 3
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomAMaxThird tests sortThreeBottomA when max value is third
func TestSortThreeBottomAMaxThird(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{5, 6, 1, 2, 3}) // Max value 3 is third of bottom 3
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomBMaxFirst tests sortThreeBottomB when max value is first
func TestSortThreeBottomBMaxFirst(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{5, 6, 3, 1, 2}) // Max value 3 is first of bottom 3
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomBMaxSecond tests sortThreeBottomB when max value is second
func TestSortThreeBottomBMaxSecond(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{5, 6, 1, 3, 2}) // Max value 3 is second of bottom 3
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}

// TestSortThreeBottomBMaxThird tests sortThreeBottomB when max value is third
func TestSortThreeBottomBMaxThird(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{5, 6, 1, 2, 3}) // Max value 3 is third of bottom 3
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 3}
	originalSize := chunk.Size
	
	sortThree(ps, chunk)
	
	// Size should decrease by 3
	if chunk.Size != originalSize-3 {
		t.Errorf("Expected size to decrease by 3, got %d", originalSize-chunk.Size)
	}
	
	// Location should change to TOP_A
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to be TOP_A, got %v", chunk.Loc)
	}
}
