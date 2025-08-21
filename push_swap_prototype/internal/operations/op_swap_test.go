package operations

import (
	"push_swap_prototype/internal/stack"
	"reflect"
	"testing"
)

// TestSwapEmptyStack tests swap on empty stack (should do nothing)
func TestSwapEmptyStack(t *testing.T) {
	s := stack.New()
	swap(s)
	if s.CurrentSize() != 0 {
		t.Error("Swap on empty stack should not change anything")
	}
}

// TestSwapSingleElement tests swap on single element (should do nothing)
func TestSwapSingleElement(t *testing.T) {
	s := stack.FromSlice([]int{1})
	swap(s)
	if s.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", s.CurrentSize())
	}
	if s.PeekValue() != 1 {
		t.Errorf("Expected top element 1, got %d", s.PeekValue())
	}
}

// TestSwapTwoElements tests swap on two elements (should swap them)
func TestSwapTwoElements(t *testing.T) {
	s := stack.FromSlice([]int{1, 2}) // top=1, second=2
	swap(s)
	expected := []int{2, 1} // after swap: top=2, second=1
	result := s.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

// TestSwapThreeElements tests swap on three elements (should only swap first two)
func TestSwapThreeElements(t *testing.T) {
	s := stack.FromSlice([]int{1, 2, 3}) // top=1, second=2, third=3
	swap(s)
	expected := []int{2, 1, 3} // after swap: top=2, second=1, third=3 (unchanged)
	result := s.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

// TestSwapMultipleElements tests swap on multiple elements (should only swap first two)
func TestSwapMultipleElements(t *testing.T) {
	s := stack.FromSlice([]int{5, 4, 3, 2, 1})
	swap(s)
	expected := []int{4, 5, 3, 2, 1} // only first two elements swapped
	result := s.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

// TestSwap_aEmptyStack tests Swap_a on empty stack A (should record operation)
func TestSwap_aEmptyStack(t *testing.T) {
	ps := NewPushSwapData()
	Swap_a(ps)
	if ps.A.CurrentSize() != 0 {
		t.Error("Swap on empty stack A should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SA {
		t.Errorf("Expected SA operation, got %v", ps.OpList[0])
	}
}

// TestSwap_aSingleElement tests Swap_a on single element in stack A (should record operation)
func TestSwap_aSingleElement(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{42})
	Swap_a(ps)
	if ps.A.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.A.CurrentSize())
	}
	if ps.A.PeekValue() != 42 {
		t.Errorf("Expected top element 42, got %d", ps.A.PeekValue())
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SA {
		t.Errorf("Expected SA operation, got %v", ps.OpList[0])
	}
}

// TestSwap_aTwoElements tests Swap_a on two elements in stack A (should swap and record)
func TestSwap_aTwoElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	Swap_a(ps)
	expected := []int{2, 1}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SA {
		t.Errorf("Expected SA operation, got %v", ps.OpList[0])
	}
}

// TestSwap_aWritingModeDisabled tests Swap_a with writing mode disabled (should swap but not record)
func TestSwap_aWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.A = stack.FromSlice([]int{3, 4})
	Swap_a(ps)
	expected := []int{4, 3}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestSwap_aStackBNotAffected tests that Swap_a doesn't affect stack B
func TestSwap_aStackBNotAffected(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	Swap_a(ps)
	expectedA := []int{2, 1}
	expectedB := []int{3, 4}
	resultA := ps.A.ToSlice()
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("Expected B %v, got %v", expectedB, resultB)
	}
}

// TestSwap_bEmptyStack tests Swap_b on empty stack B (should record operation)
func TestSwap_bEmptyStack(t *testing.T) {
	ps := NewPushSwapData()
	Swap_b(ps)
	if ps.B.CurrentSize() != 0 {
		t.Error("Swap on empty stack B should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SB {
		t.Errorf("Expected SB operation, got %v", ps.OpList[0])
	}
}

// TestSwap_bSingleElement tests Swap_b on single element in stack B (should record operation)
func TestSwap_bSingleElement(t *testing.T) {
	ps := NewPushSwapData()
	ps.B = stack.FromSlice([]int{42})
	Swap_b(ps)
	if ps.B.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.B.CurrentSize())
	}
	if ps.B.PeekValue() != 42 {
		t.Errorf("Expected top element 42, got %d", ps.B.PeekValue())
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SB {
		t.Errorf("Expected SB operation, got %v", ps.OpList[0])
	}
}

// TestSwap_bTwoElements tests Swap_b on two elements in stack B (should swap and record)
func TestSwap_bTwoElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.B = stack.FromSlice([]int{5, 6})
	Swap_b(ps)
	expected := []int{6, 5}
	result := ps.B.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SB {
		t.Errorf("Expected SB operation, got %v", ps.OpList[0])
	}
}

// TestSwap_bWritingModeDisabled tests Swap_b with writing mode disabled (should swap but not record)
func TestSwap_bWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.B = stack.FromSlice([]int{7, 8})
	Swap_b(ps)
	expected := []int{8, 7}
	result := ps.B.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestSwap_bStackANotAffected tests that Swap_b doesn't affect stack A
func TestSwap_bStackANotAffected(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	Swap_b(ps)
	expectedA := []int{1, 2}
	expectedB := []int{4, 3}
	resultA := ps.A.ToSlice()
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("Expected B %v, got %v", expectedB, resultB)
	}
}

// TestSwap_abEmptyStacks tests Swap_ab on empty stacks (should record operation)
func TestSwap_abEmptyStacks(t *testing.T) {
	ps := NewPushSwapData()
	Swap_ab(ps)
	if ps.A.CurrentSize() != 0 || ps.B.CurrentSize() != 0 {
		t.Error("Swap on empty stacks should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SS {
		t.Errorf("Expected SS operation, got %v", ps.OpList[0])
	}
}

// TestSwap_abOneElementEach tests Swap_ab with one element in each stack (should record operation)
func TestSwap_abOneElementEach(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1})
	ps.B = stack.FromSlice([]int{2})
	Swap_ab(ps)
	if ps.A.PeekValue() != 1 || ps.B.PeekValue() != 2 {
		t.Error("Single elements should not be swapped")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SS {
		t.Errorf("Expected SS operation, got %v", ps.OpList[0])
	}
}

// TestSwap_abTwoElementsStackAOnly tests Swap_ab with two elements in stack A only
func TestSwap_abTwoElementsStackAOnly(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.New() // empty
	Swap_ab(ps)
	expectedA := []int{2, 1}
	resultA := ps.A.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("Expected A %v, got %v", expectedA, resultA)
	}
	if ps.B.CurrentSize() != 0 {
		t.Error("Stack B should remain empty")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SS {
		t.Errorf("Expected SS operation, got %v", ps.OpList[0])
	}
}

// TestSwap_abTwoElementsStackBOnly tests Swap_ab with two elements in stack B only
func TestSwap_abTwoElementsStackBOnly(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.New() // empty
	ps.B = stack.FromSlice([]int{3, 4})
	Swap_ab(ps)
	expectedB := []int{4, 3}
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("Expected B %v, got %v", expectedB, resultB)
	}
	if ps.A.CurrentSize() != 0 {
		t.Error("Stack A should remain empty")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SS {
		t.Errorf("Expected SS operation, got %v", ps.OpList[0])
	}
}

// TestSwap_abTwoElementsBothStacks tests Swap_ab with two elements in both stacks
func TestSwap_abTwoElementsBothStacks(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	Swap_ab(ps)
	expectedA := []int{2, 1}
	expectedB := []int{4, 3}
	resultA := ps.A.ToSlice()
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("Expected B %v, got %v", expectedB, resultB)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != SS {
		t.Errorf("Expected SS operation, got %v", ps.OpList[0])
	}
}

// TestSwap_abWritingModeDisabled tests Swap_ab with writing mode disabled
func TestSwap_abWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.A = stack.FromSlice([]int{5, 6})
	ps.B = stack.FromSlice([]int{7, 8})
	Swap_ab(ps)
	expectedA := []int{6, 5}
	expectedB := []int{8, 7}
	resultA := ps.A.ToSlice()
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("Expected B %v, got %v", expectedB, resultB)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestSwapCLikeBehavior tests that Go implementation behaves exactly like C implementation
func TestSwapCLikeBehavior(t *testing.T) {
	// C implementation checks if second element exists by checking if it's 0
	// This test verifies our Go implementation matches this behavior
	ps := NewPushSwapData()
	
	// Test with ranks like C would produce
	ps.A = stack.FromSlice([]int{2, 1}) // ranks from C implementation
	Swap_a(ps)
	expected := []int{1, 2}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}
