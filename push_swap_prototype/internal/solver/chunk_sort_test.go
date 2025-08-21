package solver

import (
	"push_swap_prototype/internal/operations"
	"testing"
)

// TestChunkSortEmptyStack tests chunk_sort with empty stack
func TestChunkSortEmptyStack(t *testing.T) {
	ps := operations.NewPushSwapData()
	
	// Should not panic with empty stack
	chunk_sort(ps)
	
	// Stack should remain empty
	if ps.A.Size() != 0 {
		t.Errorf("Expected stack A to remain empty, got size %d", ps.A.Size())
	}
}

// TestChunkSortSingleElement tests chunk_sort with single element
func TestChunkSortSingleElement(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(2)
	ps.A.FillFromSlice([]int{42})
	
	chunk_sort(ps)
	
	// Single element should remain unchanged
	if ps.A.Size() != 1 {
		t.Errorf("Expected stack A to have 1 element, got %d", ps.A.Size())
	}
	if ps.A.GetValueAtPosition(1) != 42 {
		t.Errorf("Expected value 42, got %d", ps.A.GetValueAtPosition(1))
	}
}

// TestChunkSortTwoElements tests chunk_sort with two elements
func TestChunkSortTwoElements(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{5, 3})
	
	chunk_sort(ps)
	
	// Two elements should be sorted
	if ps.A.Size() != 2 {
		t.Errorf("Expected stack A to have 2 elements, got %d", ps.A.Size())
	}
	
	// Check if sorted (ascending order)
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	if first > second {
		t.Errorf("Expected sorted order, got %d > %d", first, second)
	}
}

// TestChunkSortThreeElements tests chunk_sort with three elements
func TestChunkSortThreeElements(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{3, 1, 2})
	
	chunk_sort(ps)
	
	// Three elements should be sorted
	if ps.A.Size() != 3 {
		t.Errorf("Expected stack A to have 3 elements, got %d", ps.A.Size())
	}
	
	// Check if sorted (ascending order)
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	third := ps.A.GetValueAtPosition(3)
	if first > second || second > third {
		t.Errorf("Expected sorted order, got %d, %d, %d", first, second, third)
	}
}

// TestChunkSortMultipleElements tests chunk_sort with multiple elements
func TestChunkSortMultipleElements(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{5, 2, 4, 1, 3})
	
	chunk_sort(ps)
	
	// All elements should be sorted
	if ps.A.Size() != 5 {
		t.Errorf("Expected stack A to have 5 elements, got %d", ps.A.Size())
	}
	
	// Check if sorted (ascending order)
	for i := 1; i < ps.A.Size(); i++ {
		current := ps.A.GetValueAtPosition(i)
		next := ps.A.GetValueAtPosition(i + 1)
		if current > next {
			t.Errorf("Expected sorted order, but %d > %d at position %d", current, next, i)
		}
	}
}

// TestRecChunkSortSmallChunk tests recChunkSort with small chunk (size <= 3)
func TestRecChunkSortSmallChunk(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{3, 1, 2})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 3}
	
	recChunkSort(ps, chunk)
	
	// Chunk should be sorted
	if ps.A.Size() != 3 {
		t.Errorf("Expected stack A to have 3 elements, got %d", ps.A.Size())
	}
	
	// Check if sorted
	first := ps.A.GetValueAtPosition(1)
	second := ps.A.GetValueAtPosition(2)
	third := ps.A.GetValueAtPosition(3)
	if first > second || second > third {
		t.Errorf("Expected sorted order, got %d, %d, %d", first, second, third)
	}
}

// TestRecChunkSortLargeChunk tests recChunkSort with large chunk (size > 3)
func TestRecChunkSortLargeChunk(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(6)
	ps.A.FillFromSlice([]int{5, 2, 4, 1, 3})
	
	chunk := &operations.Chunk{Loc: operations.TOP_A, Size: 5}
	
	recChunkSort(ps, chunk)
	
	// Chunk should be sorted
	if ps.A.Size() != 5 {
		t.Errorf("Expected stack A to have 5 elements, got %d", ps.A.Size())
	}
	
	// Check if sorted
	for i := 1; i < ps.A.Size(); i++ {
		current := ps.A.GetValueAtPosition(i)
		next := ps.A.GetValueAtPosition(i + 1)
		if current > next {
			t.Errorf("Expected sorted order, but %d > %d at position %d", current, next, i)
		}
	}
}

// TestChunkToTheTopBottomB tests chunkToTheTop for BOTTOM_B location
func TestChunkToTheTopBottomB(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.B.FillFromSlice([]int{10, 20, 30})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_B, Size: 3}
	
	chunkToTheTop(ps, chunk)
	
	// Location should change to TOP_B when size matches stack size
	if chunk.Loc != operations.TOP_B {
		t.Errorf("Expected location to change to TOP_B, got %v", chunk.Loc)
	}
}

// TestChunkToTheTopBottomA tests chunkToTheTop for BOTTOM_A location
func TestChunkToTheTopBottomA(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{1, 2, 3})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 3}
	
	chunkToTheTop(ps, chunk)
	
	// Location should change to TOP_A when size matches stack size
	if chunk.Loc != operations.TOP_A {
		t.Errorf("Expected location to change to TOP_A, got %v", chunk.Loc)
	}
}

// TestChunkToTheTopNoChange tests chunkToTheTop when no change is needed
func TestChunkToTheTopNoChange(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(4)
	ps.A.FillFromSlice([]int{1, 2})
	
	chunk := &operations.Chunk{Loc: operations.BOTTOM_A, Size: 1}
	
	originalLoc := chunk.Loc
	chunkToTheTop(ps, chunk)
	
	// Location should not change when size doesn't match stack size
	if chunk.Loc != originalLoc {
		t.Errorf("Expected location to remain unchanged, got %v", chunk.Loc)
	}
}

// TestChunkToTheTopTopLocations tests chunkToTheTop for TOP locations
func TestChunkToTheTopTopLocations(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(3)
	ps.A.FillFromSlice([]int{1, 2})
	ps.B.FillFromSlice([]int{10})
	
	// Test TOP_A
	chunkA := &operations.Chunk{Loc: operations.TOP_A, Size: 2}
	originalLocA := chunkA.Loc
	chunkToTheTop(ps, chunkA)
	if chunkA.Loc != originalLocA {
		t.Errorf("TOP_A location should not change, got %v", chunkA.Loc)
	}
	
	// Test TOP_B
	chunkB := &operations.Chunk{Loc: operations.TOP_B, Size: 1}
	originalLocB := chunkB.Loc
	chunkToTheTop(ps, chunkB)
	if chunkB.Loc != originalLocB {
		t.Errorf("TOP_B location should not change, got %v", chunkB.Loc)
	}
}

// TestChunkSortComplexScenario tests chunk_sort with a complex scenario
func TestChunkSortComplexScenario(t *testing.T) {
	ps := operations.NewPushSwapDataWithCapacity(8)
	ps.A.FillFromSlice([]int{8, 3, 6, 1, 5, 2, 7, 4})
	
	chunk_sort(ps)
	
	// All elements should be sorted
	if ps.A.Size() != 8 {
		t.Errorf("Expected stack A to have 8 elements, got %d", ps.A.Size())
	}
	
	// Check if sorted (ascending order)
	for i := 1; i < ps.A.Size(); i++ {
		current := ps.A.GetValueAtPosition(i)
		next := ps.A.GetValueAtPosition(i + 1)
		if current > next {
			t.Errorf("Expected sorted order, but %d > %d at position %d", current, next, i)
		}
	}
	
	// Verify specific values
	expected := []int{1, 2, 3, 4, 5, 6, 7, 8}
	for i, exp := range expected {
		actual := ps.A.GetValueAtPosition(i + 1)
		if actual != exp {
			t.Errorf("Expected %d at position %d, got %d", exp, i+1, actual)
		}
	}
}
