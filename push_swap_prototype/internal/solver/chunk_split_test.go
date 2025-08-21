package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

// TestInitSize tests the initSize function
func TestInitSize(t *testing.T) {
	min := &operations.Chunk{Loc: operations.TOP_A, Size: 5}
	mid := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	max := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 7}
	
	initSize(min, mid, max)
	
	if min.Size != 0 {
		t.Errorf("Expected min.Size to be 0, got %d", min.Size)
	}
	if mid.Size != 0 {
		t.Errorf("Expected mid.Size to be 0, got %d", mid.Size)
	}
	if max.Size != 0 {
		t.Errorf("Expected max.Size to be 0, got %d", max.Size)
	}
	
	// Locations should remain unchanged
	if min.Loc != operations.TOP_A {
		t.Errorf("Expected min.Loc to remain TOP_A, got %v", min.Loc)
	}
	if mid.Loc != operations.TOP_B {
		t.Errorf("Expected mid.Loc to remain TOP_B, got %v", mid.Loc)
	}
	if max.Loc != operations.BOTTOM_A {
		t.Errorf("Expected max.Loc to remain BOTTOM_A, got %v", max.Loc)
	}
}

// TestSetSplitLocTopA tests setSplitLoc for TOP_A location
func TestSetSplitLocTopA(t *testing.T) {
	min := &operations.Chunk{}
	mid := &operations.Chunk{}
	max := &operations.Chunk{}
	
	setSplitLoc(operations.TOP_A, min, mid, max)
	
	if min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected min.Loc to be BOTTOM_B, got %v", min.Loc)
	}
	if mid.Loc != operations.TOP_B {
		t.Errorf("Expected mid.Loc to be TOP_B, got %v", mid.Loc)
	}
	if max.Loc != operations.BOTTOM_A {
		t.Errorf("Expected max.Loc to be BOTTOM_A, got %v", max.Loc)
	}
}

// TestSetSplitLocBottomA tests setSplitLoc for BOTTOM_A location
func TestSetSplitLocBottomA(t *testing.T) {
	min := &operations.Chunk{}
	mid := &operations.Chunk{}
	max := &operations.Chunk{}
	
	setSplitLoc(operations.BOTTOM_A, min, mid, max)
	
	if min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected min.Loc to be BOTTOM_B, got %v", min.Loc)
	}
	if mid.Loc != operations.TOP_B {
		t.Errorf("Expected mid.Loc to be TOP_B, got %v", mid.Loc)
	}
	if max.Loc != operations.TOP_A {
		t.Errorf("Expected max.Loc to be TOP_A, got %v", max.Loc)
	}
}

// TestSetSplitLocTopB tests setSplitLoc for TOP_B location
func TestSetSplitLocTopB(t *testing.T) {
	min := &operations.Chunk{}
	mid := &operations.Chunk{}
	max := &operations.Chunk{}
	
	setSplitLoc(operations.TOP_B, min, mid, max)
	
	if min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected min.Loc to be BOTTOM_B, got %v", min.Loc)
	}
	if mid.Loc != operations.BOTTOM_A {
		t.Errorf("Expected mid.Loc to be BOTTOM_A, got %v", mid.Loc)
	}
	if max.Loc != operations.TOP_A {
		t.Errorf("Expected max.Loc to be TOP_A, got %v", max.Loc)
	}
}

// TestSetSplitLocBottomB tests setSplitLoc for BOTTOM_B location
func TestSetSplitLocBottomB(t *testing.T) {
	min := &operations.Chunk{}
	mid := &operations.Chunk{}
	max := &operations.Chunk{}
	
	setSplitLoc(operations.BOTTOM_B, min, mid, max)
	
	if min.Loc != operations.TOP_B {
		t.Errorf("Expected min.Loc to be TOP_B, got %v", min.Loc)
	}
	if mid.Loc != operations.BOTTOM_A {
		t.Errorf("Expected mid.Loc to be BOTTOM_A, got %v", mid.Loc)
	}
	if max.Loc != operations.TOP_A {
		t.Errorf("Expected max.Loc to be TOP_A, got %v", max.Loc)
	}
}

// TestSetThirdPivotsTopA tests setThirdPivots for TOP_A location
func TestSetThirdPivotsTopA(t *testing.T) {
	var pivot1, pivot2 int
	crtSize := 9
	
	setThirdPivots(operations.TOP_A, crtSize, &pivot1, &pivot2)
	
	expectedPivot2 := 9 / 3 // 3
	expectedPivot1 := 2 * 9 / 3 // 6 (like C implementation: 2 * crtSize / 3)
	
	if pivot2 != expectedPivot2 {
		t.Errorf("Expected pivot2 to be %d, got %d", expectedPivot2, pivot2)
	}
	if pivot1 != expectedPivot1 {
		t.Errorf("Expected pivot1 to be %d, got %d", expectedPivot1, pivot1)
	}
}

// TestSetThirdPivotsTopASmallSize tests setThirdPivots for TOP_A with small size
func TestSetThirdPivotsTopASmallSize(t *testing.T) {
	var pivot1, pivot2 int
	crtSize := 10 // Less than 15
	
	setThirdPivots(operations.TOP_A, crtSize, &pivot1, &pivot2)
	
	expectedPivot2 := 10 / 3 // 3
	expectedPivot1 := 2 * 10 / 3 // 6 (like C implementation: 2 * crtSize / 3)
	
	if pivot2 != expectedPivot2 {
		t.Errorf("Expected pivot2 to be %d, got %d", expectedPivot2, pivot2)
	}
	if pivot1 != expectedPivot1 {
		t.Errorf("Expected pivot1 to be %d, got %d", expectedPivot1, pivot1)
	}
}

// TestSetThirdPivotsTopB tests setThirdPivots for TOP_B location
func TestSetThirdPivotsTopB(t *testing.T) {
	var pivot1, pivot2 int
	crtSize := 8
	
	setThirdPivots(operations.TOP_B, crtSize, &pivot1, &pivot2)
	
	expectedPivot2 := 8 / 3 // 2
	expectedPivot1 := 8 / 2 // 4
	
	if pivot2 != expectedPivot2 {
		t.Errorf("Expected pivot2 to be %d, got %d", expectedPivot2, pivot2)
	}
	if pivot1 != expectedPivot1 {
		t.Errorf("Expected pivot1 to be %d, got %d", expectedPivot1, pivot1)
	}
}

// TestSetThirdPivotsBottomB tests setThirdPivots for BOTTOM_B location
func TestSetThirdPivotsBottomB(t *testing.T) {
	var pivot1, pivot2 int
	crtSize := 6 // Less than 8
	
	setThirdPivots(operations.BOTTOM_B, crtSize, &pivot1, &pivot2)
	
	expectedPivot2 := 6 / 3 // 2 (like C implementation: crtSize / 3)
	expectedPivot1 := 6 / 2 // 3
	
	if pivot2 != expectedPivot2 {
		t.Errorf("Expected pivot2 to be %d, got %d", expectedPivot2, pivot2)
	}
	if pivot1 != expectedPivot1 {
		t.Errorf("Expected pivot1 to be %d, got %d", expectedPivot1, pivot1)
	}
}

// TestSetThirdPivotsBottomBLargeSize tests setThirdPivots for BOTTOM_B with large size
func TestSetThirdPivotsBottomBLargeSize(t *testing.T) {
	var pivot1, pivot2 int
	crtSize := 12 // Greater than 8
	
	setThirdPivots(operations.BOTTOM_B, crtSize, &pivot1, &pivot2)
	
	expectedPivot2 := 12 / 3 // 4 (normal case for BOTTOM_B >= 8)
	expectedPivot1 := 12 / 2 // 6
	
	if pivot2 != expectedPivot2 {
		t.Errorf("Expected pivot2 to be %d, got %d", expectedPivot2, pivot2)
	}
	if pivot1 != expectedPivot1 {
		t.Errorf("Expected pivot1 to be %d, got %d", expectedPivot1, pivot1)
	}
}

// TestSetThirdPivotsEdgeCases tests setThirdPivots with edge case sizes
func TestSetThirdPivotsEdgeCases(t *testing.T) {
	var pivot1, pivot2 int
	
	// Test with size 1
	setThirdPivots(operations.TOP_A, 1, &pivot1, &pivot2)
	if pivot2 != 0 {
		t.Errorf("Expected pivot2 to be 0 for size 1, got %d", pivot2)
	}
	if pivot1 != 0 {
		t.Errorf("Expected pivot1 to be 0 for size 1, got %d", pivot1)
	}
	
	// Test with size 0
	setThirdPivots(operations.TOP_B, 0, &pivot1, &pivot2)
	if pivot2 != 0 {
		t.Errorf("Expected pivot2 to be 0 for size 0, got %d", pivot2)
	}
	if pivot1 != 0 {
		t.Errorf("Expected pivot1 to be 0 for size 0, got %d", pivot1)
	}
}

// TestChunkSplitTopA tests chunk_split for TOP_A location
func TestChunkSplitTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(10)
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5, 6, 7, 8, 9})
	
	toSplit := &operations.Chunk{Loc: operations.TOP_A, Size: 9}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk was fully processed
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to be 0 after splitting, got %d", toSplit.Size)
	}
	
	// Check that destination chunks have been initialized
	if dest.Min.Size == 0 && dest.Mid.Size == 0 && dest.Max.Size == 0 {
		t.Error("Expected at least one destination chunk to have elements")
	}
	
	// Check that locations are set correctly
	if dest.Min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected dest.Min.Loc to be BOTTOM_B, got %v", dest.Min.Loc)
	}
	if dest.Mid.Loc != operations.TOP_B {
		t.Errorf("Expected dest.Mid.Loc to be TOP_B, got %v", dest.Mid.Loc)
	}
	if dest.Max.Loc != operations.BOTTOM_A {
		t.Errorf("Expected dest.Max.Loc to be BOTTOM_A, got %v", dest.Max.Loc)
	}
}

// TestChunkSplitTopB tests chunk_split for TOP_B location
func TestChunkSplitTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(8)
	ps.B.FillFromSlice([]int{10, 20, 30, 40, 50, 60})
	
	toSplit := &operations.Chunk{Loc: operations.TOP_B, Size: 6}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk was fully processed
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to be 0 after splitting, got %d", toSplit.Size)
	}
	
	// Check that locations are set correctly
	if dest.Min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected dest.Min.Loc to be BOTTOM_B, got %v", dest.Min.Loc)
	}
	if dest.Mid.Loc != operations.BOTTOM_A {
		t.Errorf("Expected dest.Mid.Loc to be BOTTOM_A, got %v", dest.Mid.Loc)
	}
	if dest.Max.Loc != operations.TOP_A {
		t.Errorf("Expected dest.Max.Loc to be TOP_A, got %v", dest.Max.Loc)
	}
}

// TestChunkSplitBottomA tests chunk_split for BOTTOM_A location
func TestChunkSplitBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(7)
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5, 6, 7})
	
	toSplit := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 7}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk was fully processed
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to be 0 after splitting, got %d", toSplit.Size)
	}
	
	// Check that locations are set correctly
	if dest.Min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected dest.Min.Loc to be BOTTOM_B, got %v", dest.Min.Loc)
	}
	if dest.Mid.Loc != operations.TOP_B {
		t.Errorf("Expected dest.Mid.Loc to be TOP_B, got %v", dest.Mid.Loc)
	}
	if dest.Max.Loc != operations.TOP_A {
		t.Errorf("Expected dest.Max.Loc to be TOP_A, got %v", dest.Max.Loc)
	}
}

// TestChunkSplitBottomB tests chunk_split for BOTTOM_B location
func TestChunkSplitBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.B.FillFromSlice([]int{10, 20, 30, 40, 50})
	
	toSplit := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 5}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk was fully processed
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to be 0 after splitting, got %d", toSplit.Size)
	}
	
	// Check that locations are set correctly
	if dest.Min.Loc != operations.TOP_B {
		t.Errorf("Expected dest.Min.Loc to be TOP_B, got %v", dest.Min.Loc)
	}
	if dest.Mid.Loc != operations.BOTTOM_A {
		t.Errorf("Expected dest.Mid.Loc to be BOTTOM_A, got %v", dest.Mid.Loc)
	}
	if dest.Max.Loc != operations.TOP_A {
		t.Errorf("Expected dest.Max.Loc to be TOP_A, got %v", dest.Max.Loc)
	}
}

// TestChunkSplitEmptyChunk tests chunk_split with empty chunk
func TestChunkSplitEmptyChunk(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{1, 2, 3})
	
	toSplit := &operations.Chunk{Loc: operations.TOP_A, Size: 0}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk size remains 0
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to remain 0, got %d", toSplit.Size)
	}
	
	// Check that all destination chunks have size 0
	if dest.Min.Size != 0 {
		t.Errorf("Expected dest.Min.Size to be 0, got %d", dest.Min.Size)
	}
	if dest.Mid.Size != 0 {
		t.Errorf("Expected dest.Mid.Size to be 0, got %d", dest.Mid.Size)
	}
	if dest.Max.Size != 0 {
		t.Errorf("Expected dest.Max.Size to be 0, got %d", dest.Max.Size)
	}
}

// TestChunkSplitSingleElement tests chunk_split with single element
func TestChunkSplitSingleElement(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{42})
	
	toSplit := &operations.Chunk{Loc: operations.TOP_A, Size: 1}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk was fully processed
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to be 0 after splitting, got %d", toSplit.Size)
	}
	
	// Check that exactly one destination chunk has size 1
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 1 {
		t.Errorf("Expected total destination size to be 1, got %d", totalSize)
	}
}

// TestChunkSplitMixedValues tests chunk_split with mixed values to test pivot logic
func TestChunkSplitMixedValues(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(9)
	ps.A.FillFromSlice([]int{1, 5, 9, 2, 6, 3, 7, 4, 8})
	
	toSplit := &operations.Chunk{Loc: operations.TOP_A, Size: 9}
	dest := &operations.SplitDest{}
	
	chunk_split(ps, toSplit, dest)
	
	// Check that the chunk was fully processed
	if toSplit.Size != 0 {
		t.Errorf("Expected toSplit.Size to be 0 after splitting, got %d", toSplit.Size)
	}
	
	// Check that all elements were distributed
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != 9 {
		t.Errorf("Expected total destination size to be 9, got %d", totalSize)
	}
	
	// Check that locations are set correctly
	if dest.Min.Loc != operations.BOTTOM_B {
		t.Errorf("Expected dest.Min.Loc to be BOTTOM_B, got %v", dest.Min.Loc)
	}
	if dest.Mid.Loc != operations.TOP_B {
		t.Errorf("Expected dest.Mid.Loc to be TOP_B, got %v", dest.Mid.Loc)
	}
	if dest.Max.Loc != operations.BOTTOM_A {
		t.Errorf("Expected dest.Max.Loc to be BOTTOM_A, got %v", dest.Max.Loc)
	}
}
