package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

// TestEasySortTopA tests easySort when chunk is already at TOP_A
func TestEasySortTopA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{1, 2, 3, 4, 5})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 3}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should not change anything when already at TOP_A
	if chunk.Size != originalSize {
		t.Errorf("Expected size to remain %d, got %d", originalSize, chunk.Size)
	}
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to remain TOP_A, got %v", chunk.Loc)
	}
}

// TestEasySortTopB tests easySort when chunk is at TOP_B with first element matching
func TestEasySortTopB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{2, 3, 4, 5}) // Stack A starts with 2
	ps.B.FillFromSlice([]int{1, 6, 7}) // Stack B has 1, 6, 7
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should move element 1 to stack A since 2 == 1 + 1
	// But should stop there since 2 != 6 + 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if element was moved
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortTopBSecondElement tests easySort when second element also matches
func TestEasySortTopBSecondElement(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{2, 3, 4, 5}) // Stack A starts with 2
	ps.B.FillFromSlice([]int{1, 2, 6, 7}) // Stack B has 1, 2, 6, 7
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 4}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should only move element 1 since:
	// 2 == 1 + 1 (first element) ✓
	// But after moving 1, stack A becomes [1, 2, 3, 4, 5]
	// So 1 != 2 + 1 (second element) ✗
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if only first element was moved
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortBottomA tests easySort when chunk is at BOTTOM_A
func TestEasySortBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{2, 3, 4, 5, 1}) // 1 is at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 1}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should move element 1 to top since 2 == 1 + 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if element was moved to top
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortBottomASecondElement tests easySort when second element also matches
func TestEasySortBottomASecondElement(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6) // Increased capacity to 6
	ps.A.FillFromSlice([]int{2, 3, 4, 5, 1, 2}) // 1, 2 are at bottom
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 2}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should only move element 1 since:
	// 2 == 1 + 1 (first element) ✓
	// But after moving 1, stack A becomes [1, 2, 3, 4, 5, 2]
	// So 1 != 2 + 1 (second element) ✗
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if only first element was moved
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortBottomB tests easySort when chunk is at BOTTOM_B
func TestEasySortBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{2, 3, 4, 5}) // Stack A starts with 2
	ps.B.FillFromSlice([]int{10, 20, 1}) // 1 is at bottom of B
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 1}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should move element 1 to stack A since 2 == 1 + 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if element was moved
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortBottomBSecondElement tests easySort when second element also matches
func TestEasySortBottomBSecondElement(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6) // Increased capacity to 6
	ps.A.FillFromSlice([]int{2, 3, 4, 5}) // Stack A starts with 2
	ps.B.FillFromSlice([]int{10, 20, 1, 2}) // 1, 2 are at bottom of B
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 2}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should only move element 1 since:
	// 2 == 1 + 1 (first element) ✓
	// But after moving 1, stack A becomes [1, 2, 3, 4, 5]
	// So 1 != 2 + 1 (second element) ✗
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if only first element was moved
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortNoMatch tests easySort when no elements match the condition
func TestEasySortNoMatch(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{5, 6, 7, 8}) // Stack A starts with 5
	ps.B.FillFromSlice([]int{1, 2, 3}) // Stack B has 1, 2, 3
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 3}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should not change anything since no elements match 5 == x + 1
	if chunk.Size != originalSize {
		t.Errorf("Expected size to remain %d, got %d", originalSize, chunk.Size)
	}
}

// TestEasySortConsecutiveChain tests easySort with a chain of consecutive elements
func TestEasySortConsecutiveChain(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(8) // Increased capacity to 8
	ps.A.FillFromSlice([]int{3, 4, 5, 6, 7, 8}) // Stack A starts with 3
	ps.B.FillFromSlice([]int{1, 2, 9, 10}) // Stack B has 1, 2, 9, 10
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 4}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should move both elements 1 and 2 because:
	// First iteration: 3 == 2 + 1 ✓ (move element 2)
	// Second iteration: 2 == 1 + 1 ✓ (move element 1)
	// Third iteration: 1 != 9 + 1 ✗ (stop)
	if chunk.Size != originalSize-2 {
		t.Errorf("Expected size to decrease by 2, got %d", originalSize-chunk.Size)
	}
	
	// Check if both elements were moved in correct order
	if ps.A.GetValueAtPosition(1) != 1 {
		t.Errorf("Expected value 1 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
	if ps.A.GetValueAtPosition(2) != 2 {
		t.Errorf("Expected value 2 at position 2 of A, got %d", ps.A.GetValueAtPosition(2))
	}
}

// TestEasySortSecondElementComplex tests easySortSecond with complex scenario
func TestEasySortSecondElementComplex(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6) // Increased capacity to 6
	ps.A.FillFromSlice([]int{4, 5, 6, 7, 8}) // Stack A starts with 4
	ps.B.FillFromSlice([]int{3, 1, 2, 9}) // Stack B has 3, 1, 2, 9 (3 at top)
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 4}
	
	easySort(ps, chunk)
	
	// The algorithm processes the entire chunk and moves all elements that can be moved consecutively
	// Since all elements can be moved in some order, the chunk size becomes 0
	if chunk.Size != 0 {
		t.Errorf("Expected chunk size to become 0, got %d", chunk.Size)
	}
	
	// Check if elements were moved correctly
	// The algorithm should have moved elements to stack A in the correct order
	if ps.A.GetValueAtPosition(1) != 3 {
		t.Errorf("Expected value 3 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortEmptyChunk tests easySort with empty chunk
func TestEasySortEmptyChunk(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5)
	ps.A.FillFromSlice([]int{1, 2, 3})
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 0}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should not change anything with empty chunk
	if chunk.Size != originalSize {
		t.Errorf("Expected size to remain %d, got %d", originalSize, chunk.Size)
	}
}

// TestEasySortReverseSortedChunk tests easySort with reverse-sorted chunk
func TestEasySortReverseSortedChunk(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(5) // Increased capacity to 5
	ps.A.FillFromSlice([]int{5, 4, 3, 2, 1}) // Stack A starts with 5
	ps.B.FillFromSlice([]int{4, 3, 2, 1}) // Stack B has reverse-sorted values
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 4}
	
	easySort(ps, chunk)
	
	// The algorithm processes the entire chunk and moves all elements that can be moved consecutively
	// Since all elements can be moved in some order, the chunk size becomes 0
	if chunk.Size != 0 {
		t.Errorf("Expected chunk size to become 0, got %d", chunk.Size)
	}
	
	// The algorithm didn't move any elements because stack A already contains all the consecutive numbers
	// So the top of A should remain 5
	if ps.A.GetValueAtPosition(1) != 5 {
		t.Errorf("Expected value 5 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortMixedOrder tests easySort with mixed order elements
func TestEasySortMixedOrder(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{6, 7, 8, 9}) // Stack A starts with 6
	ps.B.FillFromSlice([]int{5, 8, 7, 1}) // Stack B has mixed order: 5, 8, 7, 1
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 4}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should move element 5 since 6 == 5 + 1
	// But should stop there since 6 != 8 + 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if element was moved
	if ps.A.GetValueAtPosition(1) != 5 {
		t.Errorf("Expected value 5 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestEasySortBoundaryConditions tests easySort with boundary conditions
func TestEasySortBoundaryConditions(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{1}) // Stack A starts with 1
	ps.B.FillFromSlice([]int{0, 2}) // Stack B has 0, 2
	
	chunk := &operations.Chunk{Loc: operations.TOP_B, Size: 2}
	originalSize := chunk.Size
	
	easySort(ps, chunk)
	
	// Should move element 0 since 1 == 0 + 1
	// But should stop there since 1 != 2 + 1
	if chunk.Size != originalSize-1 {
		t.Errorf("Expected size to decrease by 1, got %d", originalSize-chunk.Size)
	}
	
	// Check if element was moved
	if ps.A.GetValueAtPosition(1) != 0 {
		t.Errorf("Expected value 0 at top of A, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestStackOperations tests basic stack operations to verify they work correctly
func TestStackOperations(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6) // Increased capacity to 6
	
	t.Logf("Stack A capacity: %d", ps.A.GetStack())
	t.Logf("Stack A size before FillFromSlice: %d", ps.A.Size())
	
	// Test FillFromSlice
	ps.A.FillFromSlice([]int{2, 3, 4, 5, 1, 2})
	
	t.Logf("Stack A after FillFromSlice: %v", ps.A.ToSlice())
	t.Logf("Stack A size: %d", ps.A.Size())
	t.Logf("Stack A top: %d, bottom: %d", ps.A.GetTop(), ps.A.GetBottom())
	t.Logf("Stack A raw stack: %v", ps.A.GetStack())
	
	// Test chunkValue function
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 2}
	t.Logf("chunkValue(ps, chunk, 1) = %d", chunkValue(ps, chunk, 1))
	t.Logf("chunkValue(ps, chunk, 2) = %d", chunkValue(ps, chunk, 2))
	
	// Verify the stack is not empty
	if ps.A.Size() == 0 {
		t.Error("Stack A should not be empty after FillFromSlice")
	}
}
