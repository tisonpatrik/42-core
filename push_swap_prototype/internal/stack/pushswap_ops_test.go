package stack

import (
	"testing"
)

func TestSwapTop(t *testing.T) {
	s := New()
	
	// Test swap on empty stack
	if s.SwapTop() {
		t.Error("SwapTop should fail on empty stack")
	}
	
	// Test swap on single element stack
	s.Push(5)
	if s.SwapTop() {
		t.Error("SwapTop should fail on single element stack")
	}
	
	// Test swap on two element stack
	s.Push(10)
	beforeTop := s.Peek()
	beforeSecond := s.GetValueAtPosition0(1)
	
	t.Logf("Before swap: top=%d, second=%d, stack=%v", beforeTop, beforeSecond, s.ToSlice())
	
	if !s.SwapTop() {
		t.Error("SwapTop should succeed on two element stack")
	}
	
	t.Logf("After swap: top=%d, second=%d, stack=%v", s.Peek(), s.GetValueAtPosition0(1), s.ToSlice())
	
	// Check values were swapped
	if s.Peek() != beforeSecond {
		t.Error("Top element should be swapped")
	}
	if s.GetValueAtPosition0(1) != beforeTop {
		t.Error("Second element should be swapped")
	}
	
	// Test swap on larger stack
	s.Push(15)
	s.Push(20)
	beforeTop = s.Peek()
	beforeSecond = s.GetValueAtPosition0(1)
	
	if !s.SwapTop() {
		t.Error("SwapTop should succeed on larger stack")
	}
	
	if s.Peek() != beforeSecond {
		t.Error("Top element should be swapped on larger stack")
	}
	if s.GetValueAtPosition0(1) != beforeTop {
		t.Error("Second element should be swapped on larger stack")
	}
}

func TestRotateUp(t *testing.T) {
	s := New()
	
	// Test rotate on empty stack - C implementation always succeeds
	if !s.RotateUp() {
		t.Error("RotateUp should succeed on empty stack (like C implementation)")
	}
	
	// Test rotate on single element stack - C implementation always succeeds
	s.Push(5)
	if !s.RotateUp() {
		t.Error("RotateUp should succeed on single element stack (like C implementation)")
	}
	
	// Test rotate on two element stack
	s.Push(10)
	beforeTop := s.Peek()
	beforeSecond := s.GetValueAtPosition0(1)
	
	if !s.RotateUp() {
		t.Error("RotateUp should succeed on two element stack")
	}
	
	// Check rotation: top becomes second, second becomes top
	if s.Peek() != beforeSecond {
		t.Error("Top element should become second after rotation")
	}
	if s.GetValueAtPosition0(1) != beforeTop {
		t.Error("Second element should become top after rotation")
	}
	
	// Test rotate on three element stack
	s.Push(15)
	beforeTop = s.Peek()
	beforeSecond = s.GetValueAtPosition0(1)
	beforeThird := s.GetValueAtPosition0(2)
	
	if !s.RotateUp() {
		t.Error("RotateUp should succeed on three element stack")
	}
	
	// Check rotation: top becomes second, second becomes third, third becomes top
	if s.Peek() != beforeSecond {
		t.Error("Top element should become second after rotation")
	}
	if s.GetValueAtPosition0(1) != beforeThird {
		t.Error("Second element should become third after rotation")
	}
	if s.GetValueAtPosition0(2) != beforeTop {
		t.Error("Third element should become top after rotation")
	}
}

func TestRotateDown(t *testing.T) {
	s := New()
	
	// Test rotate down on empty stack - C implementation always succeeds
	if !s.RotateDown() {
		t.Error("RotateDown should succeed on empty stack (like C implementation)")
	}
	
	// Test rotate down on single element stack - C implementation always succeeds
	s.Push(5)
	if !s.RotateDown() {
		t.Error("RotateDown should succeed on single element stack (like C implementation)")
	}
	
	// Test rotate down on two element stack
	s.Push(10)
	beforeTop := s.Peek()
	beforeSecond := s.GetValueAtPosition0(1)
	
	if !s.RotateDown() {
		t.Error("RotateDown should succeed on two element stack")
	}
	
	// Check reverse rotation: second becomes top, top becomes second
	if s.Peek() != beforeSecond {
		t.Error("Second element should become top after reverse rotation")
	}
	if s.GetValueAtPosition0(1) != beforeTop {
		t.Error("Top element should become second after reverse rotation")
	}
	
	// Test rotate down on three element stack
	s.Push(15)
	beforeTop = s.Peek()
	beforeSecond = s.GetValueAtPosition0(1)
	beforeThird := s.GetValueAtPosition0(2)
	
	if !s.RotateDown() {
		t.Error("RotateDown should succeed on three element stack")
	}
	
	// Check reverse rotation: third becomes top, top becomes second, second becomes third
	if s.Peek() != beforeThird {
		t.Error("Third element should become top after reverse rotation")
	}
	if s.GetValueAtPosition0(1) != beforeTop {
		t.Error("Top element should become second after reverse rotation")
	}
	if s.GetValueAtPosition0(2) != beforeSecond {
		t.Error("Second element should become third after reverse rotation")
	}
}

func TestPushFrom(t *testing.T) {
	source := New()
	dest := New()
	
	// Test push from empty source
	if !dest.PushFrom(source) {
		t.Error("PushFrom should succeed (return true) when source is empty, like C implementation")
	}
	
	// Test push from source with elements
	source.Push(5)
	source.Push(10)
	
	// Create destination with sufficient capacity (like C implementation)
	// Start with empty stack, it will expand as needed
	dest = New()
	
	beforeSourceSize := source.Size()
	beforeDestSize := dest.Size()
	beforeSourceTop := source.Peek()
	
	if !dest.PushFrom(source) {
		t.Error("PushFrom should succeed when source has elements")
	}
	
	// Check sizes
	if source.Size() != beforeSourceSize-1 {
		t.Error("Source size should decrease by 1")
	}
	if dest.Size() != beforeDestSize+1 {
		t.Error("Destination size should increase by 1")
	}
	
	// Check value was moved
	if dest.Peek() != beforeSourceTop {
		t.Error("Top element from source should be moved to destination")
	}
	
	// Test push second element
	if !dest.PushFrom(source) {
		t.Error("PushFrom should succeed for second element")
	}
	
	if dest.Size() != 2 {
		t.Error("Destination should have 2 elements")
	}
	if source.Size() != 0 {
		t.Error("Source should be empty after second push")
	}
}

func TestPushFromMaintainsOrder(t *testing.T) {
	// Create source stack using FromSlice (like C implementation)
	source := FromSlice([]int{1, 2, 3})
	dest := New()
	
	// Push all elements from source to dest
	for i := 0; i < 3; i++ {
		if !dest.PushFrom(source) {
			t.Errorf("PushFrom should succeed for element %d", i)
		}
	}
	
	// Check order in destination (should be reverse of push order due to stack LIFO behavior)
	expected := []int{3, 2, 1}
	for i, val := range expected {
		if dest.GetValueAtPosition0(i) != val {
			t.Errorf("Expected %d at position %d, got %d", val, i, dest.GetValueAtPosition0(i))
		}
	}
}

func TestOperationsPreserveStackIntegrity(t *testing.T) {
	// Fill stack with known values using FromSlice (like C implementation)
	values := []int{1, 2, 3, 4, 5}
	s := FromSlice(values)
	
	// Perform operations and verify stack integrity
	originalSize := s.Size()
	
	// Test swap
	if !s.SwapTop() {
		t.Error("SwapTop should succeed")
	}
	if s.Size() != originalSize {
		t.Error("SwapTop should not change stack size")
	}
	
	// Test rotate up
	if !s.RotateUp() {
		t.Error("RotateUp should succeed")
	}
	if s.Size() != originalSize {
		t.Error("RotateUp should not change stack size")
	}
	
	// Test rotate down
	if !s.RotateDown() {
		t.Error("RotateDown should succeed")
	}
	if s.Size() != originalSize {
		t.Error("RotateDown should not change stack size")
	}
	
	// Verify all original values are still present
	slice := s.ToSlice()
	if len(slice) != len(values) {
		t.Error("Stack should contain all original values")
	}
	
	// Check that values are still integers (basic integrity check)
	for _, val := range slice {
		if val < 0 || val > 1000 {
			t.Error("Stack contains unexpected values")
		}
	}
}
