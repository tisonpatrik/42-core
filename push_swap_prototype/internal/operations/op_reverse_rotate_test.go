package operations

import (
	"push_swap_prototype/internal/stack"
	"reflect"
	"testing"
)

// TestR_rotateEmptyStack tests r_rotate on empty stack (should do nothing but record operation)
func TestR_rotateEmptyStack(t *testing.T) {
	ps := NewPushSwapData()
	R_rotate_a(ps)
	if ps.A.CurrentSize() != 0 {
		t.Error("R_rotate on empty stack A should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRA {
		t.Errorf("Expected RRA operation, got %v", ps.OpList[0])
	}
}

// TestR_rotateSingleElement tests r_rotate on single element (should do nothing but record operation)
func TestR_rotateSingleElement(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{42})
	R_rotate_a(ps)
	if ps.A.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.A.CurrentSize())
	}
	if ps.A.PeekValue() != 42 {
		t.Errorf("Expected top element 42, got %d", ps.A.PeekValue())
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRA {
		t.Errorf("Expected RRA operation, got %v", ps.OpList[0])
	}
}

// TestR_rotateTwoElements tests r_rotate on two elements (should reverse rotate them)
func TestR_rotateTwoElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2}) // top=1, second=2
	R_rotate_a(ps)
	expected := []int{2, 1} // after r_rotate: top=2, second=1
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRA {
		t.Errorf("Expected RRA operation, got %v", ps.OpList[0])
	}
}

// TestR_rotateThreeElements tests r_rotate on three elements (should reverse rotate all)
func TestR_rotateThreeElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2, 3}) // top=1, second=2, third=3
	R_rotate_a(ps)
	expected := []int{3, 1, 2} // after r_rotate: top=3, second=1, third=2
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRA {
		t.Errorf("Expected RRA operation, got %v", ps.OpList[0])
	}
}

// TestR_rotateMultipleElements tests r_rotate on multiple elements
func TestR_rotateMultipleElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{5, 4, 3, 2, 1})
	R_rotate_a(ps)
	expected := []int{1, 5, 4, 3, 2} // after r_rotate: top=1, second=5, third=4, fourth=3, fifth=2
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRA {
		t.Errorf("Expected RRA operation, got %d", ps.OpList[0])
	}
}

// TestR_rotate_aWritingModeDisabled tests R_rotate_a with writing mode disabled
func TestR_rotate_aWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.A = stack.FromSlice([]int{3, 4})
	R_rotate_a(ps)
	expected := []int{4, 3}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestR_rotate_aStackBNotAffected tests that R_rotate_a doesn't affect stack B
func TestR_rotate_aStackBNotAffected(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	R_rotate_a(ps)
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

// TestR_rotate_bEmptyStack tests R_rotate_b on empty stack B
func TestR_rotate_bEmptyStack(t *testing.T) {
	ps := NewPushSwapData()
	R_rotate_b(ps)
	if ps.B.CurrentSize() != 0 {
		t.Error("R_rotate on empty stack B should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRB {
		t.Errorf("Expected RRB operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_bSingleElement tests R_rotate_b on single element in stack B
func TestR_rotate_bSingleElement(t *testing.T) {
	ps := NewPushSwapData()
	ps.B = stack.FromSlice([]int{42})
	R_rotate_b(ps)
	if ps.B.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.B.CurrentSize())
	}
	if ps.B.PeekValue() != 42 {
		t.Errorf("Expected top element 42, got %d", ps.B.PeekValue())
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRB {
		t.Errorf("Expected RRB operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_bTwoElements tests R_rotate_b on two elements in stack B
func TestR_rotate_bTwoElements(t *testing.T) {
	ps := NewPushSwapData()
	ps.B = stack.FromSlice([]int{5, 6})
	R_rotate_b(ps)
	expected := []int{6, 5}
	result := ps.B.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRB {
		t.Errorf("Expected RRB operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_bWritingModeDisabled tests R_rotate_b with writing mode disabled
func TestR_rotate_bWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.B = stack.FromSlice([]int{7, 8})
	R_rotate_b(ps)
	expected := []int{8, 7}
	result := ps.B.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
	if len(ps.OpList) != 0 {
		t.Error("No operation should be saved when WritingMode is false")
	}
}

// TestR_rotate_bStackANotAffected tests that R_rotate_b doesn't affect stack A
func TestR_rotate_bStackANotAffected(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	R_rotate_b(ps)
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

// TestR_rotate_abEmptyStacks tests R_rotate_ab on empty stacks
func TestR_rotate_abEmptyStacks(t *testing.T) {
	ps := NewPushSwapData()
	R_rotate_ab(ps)
	if ps.A.CurrentSize() != 0 || ps.B.CurrentSize() != 0 {
		t.Error("R_rotate on empty stacks should not change anything")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRR {
		t.Errorf("Expected RRR operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_abOneElementEach tests R_rotate_ab with one element in each stack
func TestR_rotate_abOneElementEach(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1})
	ps.B = stack.FromSlice([]int{2})
	R_rotate_ab(ps)
	if ps.A.PeekValue() != 1 || ps.B.PeekValue() != 2 {
		t.Error("Single elements should not be reverse rotated")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != RRR {
		t.Errorf("Expected RRR operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_abTwoElementsStackAOnly tests R_rotate_ab with two elements in stack A only
func TestR_rotate_abTwoElementsStackAOnly(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.New() // empty
	R_rotate_ab(ps)
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
	if ps.OpList[0] != RRR {
		t.Errorf("Expected RRR operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_abTwoElementsStackBOnly tests R_rotate_ab with two elements in stack B only
func TestR_rotate_abTwoElementsStackBOnly(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.New() // empty
	ps.B = stack.FromSlice([]int{3, 4})
	R_rotate_ab(ps)
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
	if ps.OpList[0] != RRR {
		t.Errorf("Expected RRR operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_abTwoElementsBothStacks tests R_rotate_ab with two elements in both stacks
func TestR_rotate_abTwoElementsBothStacks(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2})
	ps.B = stack.FromSlice([]int{3, 4})
	R_rotate_ab(ps)
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
	if ps.OpList[0] != RRR {
		t.Errorf("Expected RRR operation, got %v", ps.OpList[0])
	}
}

// TestR_rotate_abWritingModeDisabled tests R_rotate_ab with writing mode disabled
func TestR_rotate_abWritingModeDisabled(t *testing.T) {
	ps := NewPushSwapData()
	ps.WritingMode = false
	ps.A = stack.FromSlice([]int{5, 6})
	ps.B = stack.FromSlice([]int{7, 8})
	R_rotate_ab(ps)
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

// TestR_rotateCLikeBehavior tests that Go implementation behaves exactly like C implementation
func TestR_rotateCLikeBehavior(t *testing.T) {
	// C implementation always performs r_rotate operation regardless of stack size
	// This test verifies our Go implementation matches this behavior
	ps := NewPushSwapData()
	
	// Test with single element - C would r_rotate it (just move pointers)
	ps.A = stack.FromSlice([]int{42})
	R_rotate_a(ps)
	// In C, this would just move pointers, so the element stays in place
	// But our Go implementation should handle this correctly
	if ps.A.CurrentSize() != 1 {
		t.Errorf("Expected size 1, got %d", ps.A.CurrentSize())
	}
	
	// Test with two elements - C would r_rotate them
	ps.A = stack.FromSlice([]int{1, 2})
	R_rotate_a(ps)
	expected := []int{2, 1}
	result := ps.A.ToSlice()
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
} 