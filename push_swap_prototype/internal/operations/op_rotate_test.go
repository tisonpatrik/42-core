package operations

import (
	"push_swap_prototype/internal/stack"
	"reflect"
	"testing"
)

// TestRotateEmptyStack tests rotate on empty stack (should do nothing but record operation)
func TestRotateEmptyStack(t *testing.T) {
	ps := NewPushSwapData()
	Rotate_a(ps)
	if ps.A.CurrentSize() != 0 {
		t.Error("Rotate on empty stack A should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RA {
		t.Errorf("Expected RA operation, got %v", ps.OpList[0])
	}
}

// TestRotateSingleElement tests rotate on single element (should do nothing but record operation)
func TestRotateSingleElement(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{42})
	Rotate_a(ps)
	if ps.A.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.A.CurrentSize())
	}
	if ps.A.PeekValue() != 42 {
		t.Errorf("Expected top element 42, got %d", ps.A.PeekValue())
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RA {
		t.Errorf("Expected RA operation, got %v", ps.OpList[0])
	}
}

// TestRotateTwoElements tests rotate on two elements (should rotate them)
func TestRotateTwoElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2}) // top=1, second=2
	Rotate_a(ps)
	expected := []int{2, 1} // after rotate: top=2, second=1
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RA {
		t.Errorf("Expected RA operation, got %v", ps.OpList[0])
	}
}

// TestRotateThreeElements tests rotate on three elements (should rotate all)
func TestRotateThreeElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2, 3}) // top=1, second=2, third=3
	Rotate_a(ps)
	expected := []int{2, 3, 1} // after rotate: top=2, second=3, third=1
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RA {
		t.Errorf("Expected RA operation, got %v", ps.OpList[0])
	}
}

// TestRotateMultipleElements tests rotate on multiple elements
func TestRotateMultipleElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{5, 4, 3, 2, 1})
	Rotate_a(ps)
	expected := []int{4, 3, 2, 1, 5} // after rotate: top=4, second=3, third=2, fourth=1, fifth=5
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RA {
		t.Errorf("Expected RA operation, got %v", ps.OpList[0])
	}
}

// TestRotate_aWritingModeDisabled tests Rotate_a with writing mode disabled
func TestRotate_aWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.A = stack.FromSlice([]int{3, 4})
	Rotate_a(ps)
	expected := []int{4, 3}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestRotate_aStackBNotAffected tests that Rotate_a doesn't affect stack B
func TestRotate_aStackBNotAffected(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	Rotate_a(ps)
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

// TestRotate_bEmptyStack tests Rotate_b on empty stack B
func TestRotate_bEmptyStack(t *testing.T) {
	ps := NewPushSwapData()
	Rotate_b(ps)
	if ps.B.CurrentSize() != 0 {
		t.Error("Rotate on empty stack B should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RB {
		t.Errorf("Expected RB operation, got %v", ps.OpList[0])
	}
}

// TestRotate_bSingleElement tests Rotate_b on single element in stack B
func TestRotate_bSingleElement(t *testing.T) {
	ps := NewPushSwapData()
	ps.B = stack.FromSlice([]int{42})
	Rotate_b(ps)
	if ps.B.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.B.CurrentSize())
	}
	if ps.B.PeekValue() != 42 {
		t.Errorf("Expected top element 42, got %d", ps.B.PeekValue())
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RB {
		t.Errorf("Expected RB operation, got %v", ps.OpList[0])
	}
}

// TestRotate_bTwoElements tests Rotate_b on two elements in stack B
func TestRotate_bTwoElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.B = stack.FromSlice([]int{5, 6})
	Rotate_b(ps)
	expected := []int{6, 5}
	result := ps.B.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RB {
		t.Errorf("Expected RB operation, got %v", ps.OpList[0])
	}
}

// TestRotate_bWritingModeDisabled tests Rotate_b with writing mode disabled
func TestRotate_bWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.B = stack.FromSlice([]int{7, 8})
	Rotate_b(ps)
	expected := []int{8, 7}
	result := ps.B.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestRotate_bStackANotAffected tests that Rotate_b doesn't affect stack A
func TestRotate_bStackANotAffected(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	Rotate_b(ps)
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

// TestRotate_abEmptyStacks tests Rotate_ab on empty stacks
func TestRotate_abEmptyStacks(t *testing.T) {
	ps := NewPushSwapData()
	Rotate_ab(ps)
	if ps.A.CurrentSize() != 0 || ps.B.CurrentSize() != 0 {
		t.Error("Rotate on empty stacks should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RR {
		t.Errorf("Expected RR operation, got %v", ps.OpList[0])
	}
}

// TestRotate_abOneElementEach tests Rotate_ab with one element in each stack
func TestRotate_abOneElementEach(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1})
	ps.B = stack.FromSlice([]int{2})
	Rotate_ab(ps)
	if ps.A.PeekValue() != 1 || ps.B.PeekValue() != 2 {
		t.Error("Single elements should not be rotated")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RR {
		t.Errorf("Expected RR operation, got %v", ps.OpList[0])
	}
}

// TestRotate_abTwoElementsStackAOnly tests Rotate_ab with two elements in stack A only
func TestRotate_abTwoElementsStackAOnly(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.New() // empty
	Rotate_ab(ps)
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
	if ps.OpList[0] != RR {
		t.Errorf("Expected RR operation, got %v", ps.OpList[0])
	}
}

// TestRotate_abTwoElementsStackBOnly tests Rotate_ab with two elements in stack B only
func TestRotate_abTwoElementsStackBOnly(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.New() // empty
	ps.B = stack.FromSlice([]int{3, 4})
	Rotate_ab(ps)
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
	if ps.OpList[0] != RR {
		t.Errorf("Expected RR operation, got %v", ps.OpList[0])
	}
}

// TestRotate_abTwoElementsBothStacks tests Rotate_ab with two elements in both stacks
func TestRotate_abTwoElementsBothStacks(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	Rotate_ab(ps)
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
	if ps.OpList[0] != RR {
		t.Errorf("Expected RR operation, got %v", ps.OpList[0])
	}
}

// TestRotate_abWritingModeDisabled tests Rotate_ab with writing mode disabled
func TestRotate_abWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.A = stack.FromSlice([]int{5, 6})
	ps.B = stack.FromSlice([]int{7, 8})
	Rotate_ab(ps)
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

// TestRotateCLikeBehavior tests that Go implementation behaves exactly like C implementation
func TestRotateCLikeBehavior(t *testing.T) {
	// C implementation always performs rotate operation regardless of stack size
	// This test verifies our Go implementation matches this behavior
	ps := NewPushSwapData()
	
	// Test with single element - C would rotate it (just move pointers)
	ps.A = stack.FromSlice([]int{42})
	Rotate_a(ps)
	// In C, this would just move pointers, so the element stays in place
	// But our Go implementation should handle this correctly
	if ps.A.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.A.CurrentSize())
	}
	
	// Test with two elements - C would rotate them
	ps.A = stack.FromSlice([]int{1, 2})
	Rotate_a(ps)
	expected := []int{2, 1}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}
