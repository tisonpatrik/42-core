package operations

import (
	"reflect"
	"testing"
)

func TestNewPushSwapData(t *testing.T) {
	ps := NewPushSwapData()
	
	// Check that stacks are initialized
	if ps.A == nil {
		t.Error("Stack A should not be nil")
	}
	if ps.B == nil {
		t.Error("Stack B should not be nil")
	}
	
	// Check that OpList is empty
	if len(ps.OpList) != 0 {
		t.Errorf("OpList should be empty, got length %d", len(ps.OpList))
	}
	
	// Check that WritingMode is true by default
	if !ps.WritingMode {
		t.Error("WritingMode should be true by default")
	}
}

func TestGetOperations(t *testing.T) {
	ps := NewPushSwapData()
	
	// Initially should be empty
	ops := ps.GetOperations()
	if len(ops) != 0 {
		t.Errorf("Expected empty operations list, got %d operations", len(ops))
	}
	
	// Add some operations manually
	ps.OpList = []Operation{SA, PA, RA}
	ops = ps.GetOperations()
	if len(ops) != 3 {
		t.Errorf("Expected 3 operations, got %d", len(ops))
	}
	
	// Check that operations are in correct order
	expected := []Operation{SA, PA, RA}
	if !reflect.DeepEqual(ops, expected) {
		t.Errorf("Expected operations %v, got %v", expected, ops)
	}
}

func TestSaveOp(t *testing.T) {
	ps := NewPushSwapData()
	
	// Test saving single operation
	saveOp(ps, SA)
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SA {
		t.Errorf("Expected operation SA, got %v", ps.OpList[0])
	}
	
	// Test saving multiple operations
	saveOp(ps, PA)
	saveOp(ps, RA)
	if len(ps.OpList) != 3 {
		t.Errorf("Expected 3 operations, got %d", len(ps.OpList))
	}
	
	expected := []Operation{SA, PA, RA}
	if !reflect.DeepEqual(ps.OpList, expected) {
		t.Errorf("Expected operations %v, got %v", expected, ps.OpList)
	}
}

func TestInitializeFromSlice(t *testing.T) {
	ps := NewPushSwapData()
	
	// Test with empty slice
	InitializeFromSlice(ps, []int{})
	if ps.A.Size() != 0 {
		t.Errorf("Expected empty stack A, got size %d", ps.A.Size())
	}
	
	// Test with single value
	InitializeFromSlice(ps, []int{42})
	if ps.A.Size() != 1 {
		t.Errorf("Expected stack A size 1, got %d", ps.A.Size())
	}
	val := ps.A.PeekValue()
	if val != 1 { // Should be converted to rank 1 (C gives ranks from 1)
		t.Errorf("Expected rank 1, got %d", val)
	}
	
	// Test with multiple values
	InitializeFromSlice(ps, []int{5, 3, 1, 4, 2})
	if ps.A.Size() != 5 {
		t.Errorf("Expected stack A size 5, got %d", ps.A.Size())
	}
	
	// Check that values are ranked (C gives ranks from 1)
	stackValues := ps.A.ToSlice()
	if len(stackValues) != 5 {
		t.Errorf("Expected 5 values in stack, got %d", len(stackValues))
	}
	
	// Verify the ranking logic (C implementation)
	// 1 is smallest, so it should get rank 1
	// 2 is second smallest, so it should get rank 2
	// 3 is third smallest, so it should get rank 3
	// 4 is fourth smallest, so it should get rank 4
	// 5 is largest, so it should get rank 5
	// FromSlice creates stack where first element is at top
	if stackValues[0] != 5 { // First element (5) should get rank 5 (largest)
		t.Errorf("Expected first element to be rank 5, got %d", stackValues[0])
	}
}

func TestOperationConstants(t *testing.T) {
	// Test that all operation constants are defined
	operations := []Operation{SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR}
	
	// Check that we have all 11 operations
	if len(operations) != 11 {
		t.Errorf("Expected 11 operations, got %d", len(operations))
	}
	
	// Check that operations are sequential starting from 0
	for i, op := range operations {
		if int(op) != i {
			t.Errorf("Expected operation %d to have value %d, got %d", i, i, int(op))
		}
	}
}

func TestOperationString(t *testing.T) {
	testCases := []struct {
		op       Operation
		expected string
	}{
		{SA, "sa"},
		{SB, "sb"},
		{SS, "ss"},
		{PA, "pa"},
		{PB, "pb"},
		{RA, "ra"},
		{RB, "rb"},
		{RR, "rr"},
		{RRA, "rra"},
		{RRB, "rrb"},
		{RRR, "rrr"},
	}
	
	for _, tc := range testCases {
		result := tc.op.String()
		if result != tc.expected {
			t.Errorf("Operation %v.String() = %s, expected %s", tc.op, result, tc.expected)
		}
	}
	
	// Test unknown operation
	unknownOp := Operation(99)
	result := unknownOp.String()
	if result != "unknown" {
		t.Errorf("Unknown operation should return 'unknown', got %s", result)
	}
}

func TestLocConstants(t *testing.T) {
	// Test that all location constants are defined
	locations := []Loc{TOP_A, BOTTOM_A, TOP_B, BOTTOM_B}
	
	// Check that we have all 4 locations
	if len(locations) != 4 {
		t.Errorf("Expected 4 locations, got %d", len(locations))
	}
	
	// Check that locations are sequential starting from 0
	for i, loc := range locations {
		if int(loc) != i {
			t.Errorf("Expected location %d to have value %d, got %d", i, i, int(loc))
		}
	}
}

func TestChunkStruct(t *testing.T) {
	chunk := Chunk{
		Loc:  TOP_A,
		Size: 5,
	}
	
	if chunk.Loc != TOP_A {
		t.Errorf("Expected location TOP_A, got %v", chunk.Loc)
	}
	
	if chunk.Size != 5 {
		t.Errorf("Expected size 5, got %d", chunk.Size)
	}
	
	// Test with different values
	chunk.Loc = BOTTOM_B
	chunk.Size = 10
	
	if chunk.Loc != BOTTOM_B {
		t.Errorf("Expected location BOTTOM_B, got %v", chunk.Loc)
	}
	
	if chunk.Size != 10 {
		t.Errorf("Expected size 10, got %d", chunk.Size)
	}
}

func TestSplitDestStruct(t *testing.T) {
	splitDest := SplitDest{
		Min: Chunk{Loc: TOP_A, Size: 3},
		Mid: Chunk{Loc: TOP_B, Size: 2},
		Max: Chunk{Loc: BOTTOM_A, Size: 4},
	}
	
	// Test Min chunk
	if splitDest.Min.Loc != TOP_A {
		t.Errorf("Expected Min.Loc to be TOP_A, got %v", splitDest.Min.Loc)
	}
	if splitDest.Min.Size != 3 {
		t.Errorf("Expected Min.Size to be 3, got %d", splitDest.Min.Size)
	}
	
	// Test Mid chunk
	if splitDest.Mid.Loc != TOP_B {
		t.Errorf("Expected Mid.Loc to be TOP_B, got %v", splitDest.Mid.Loc)
	}
	if splitDest.Mid.Size != 2 {
		t.Errorf("Expected Mid.Size to be 2, got %d", splitDest.Mid.Size)
	}
	
	// Test Max chunk
	if splitDest.Max.Loc != BOTTOM_A {
		t.Errorf("Expected Max.Loc to be BOTTOM_A, got %v", splitDest.Max.Loc)
	}
	if splitDest.Max.Size != 4 {
		t.Errorf("Expected Max.Size to be 4, got %d", splitDest.Max.Size)
	}
}

func TestWritingMode(t *testing.T) {
	ps := NewPushSwapData()
	
	// Test that operations are saved when WritingMode is true
	ps.WritingMode = true
	saveOp(ps, SA)
	if len(ps.OpList) != 1 {
		t.Error("Operation should be saved when WritingMode is true")
	}
	
	// Test that operations are not saved when WritingMode is false
	ps.WritingMode = false
	ps.OpList = []Operation{} // Clear the list
	saveOp(ps, PA)
	if len(ps.OpList) != 0 {
		t.Error("Operation should not be saved when WritingMode is false")
	}
}

func TestStackIntegration(t *testing.T) {
	ps := NewPushSwapData()
	
	// Test that stacks are properly initialized
	if ps.A.Size() != 0 {
		t.Errorf("Stack A should start empty, got size %d", ps.A.Size())
	}
	if ps.B.Size() != 0 {
		t.Errorf("Stack B should start empty, got size %d", ps.B.Size())
	}
	
	// Test that we can push to stacks
	ps.A.Push(42)
	ps.B.Push(24)
	
	if ps.A.Size() != 1 {
		t.Errorf("Stack A should have size 1, got %d", ps.A.Size())
	}
	if ps.B.Size() != 1 {
		t.Errorf("Stack B should have size 1, got %d", ps.B.Size())
	}
	
	if ps.A.PeekValue() != 42 {
		t.Errorf("Stack A top should be 42, got %d", ps.A.PeekValue())
	}
	if ps.B.PeekValue() != 24 {
		t.Errorf("Stack B top should be 24, got %d", ps.B.PeekValue())
	}
}

func TestOperationListModification(t *testing.T) {
	ps := NewPushSwapData()
	
	// Test that we can modify the operation list directly
	ps.OpList = append(ps.OpList, SA, PA, RA)
	
	// Test that GetOperations returns the modified list
	ops := ps.GetOperations()
	if len(ops) != 3 {
		t.Errorf("Expected 3 operations, got %d", len(ops))
	}
	
	// Test that we can clear the list
	ps.OpList = []Operation{}
	ops = ps.GetOperations()
	if len(ops) != 0 {
		t.Errorf("Expected empty operations list, got %d operations", len(ops))
	}
}

func TestEdgeCases(t *testing.T) {
	ps := NewPushSwapData()
	
	// Test with nil values (should not panic)
	ps.A = nil
	ps.B = nil
	
	// Test GetOperations with nil OpList
	ps.OpList = nil
	ops := ps.GetOperations()
	if ops == nil {
		t.Error("GetOperations should not return nil, should return empty slice")
	}
	if len(ops) != 0 {
		t.Errorf("Expected empty slice, got length %d", len(ops))
	}
	
	// Test InitializeFromSlice with nil data
	InitializeFromSlice(nil, []int{1, 2, 3})
	// Should not panic
	
	// Test saveOp with nil data
	saveOp(nil, SA)
	// Should not panic
}
