package stack

import (
	"reflect"
	"testing"
)

func TestNew(t *testing.T) {
	s := New()
	
	if s.stack == nil {
		t.Error("Stack slice should not be nil")
	}
	if s.size != 0 {
		t.Errorf("Expected size 0, got %d", s.size)
	}
	if s.top != 0 {
		t.Errorf("Expected top 0, got %d", s.top)
	}
	if s.bottom != 0 {
		t.Errorf("Expected bottom 0, got %d", s.bottom)
	}
}

func TestPush(t *testing.T) {
	s := New()
	
	// Push first element
	s.Push(5)
	if s.size != 1 {
		t.Errorf("Expected size 1, got %d", s.size)
	}
	if s.top != 0 {
		t.Errorf("Expected top 0, got %d", s.top)
	}
	if s.bottom != 0 {
		t.Errorf("Expected bottom 0, got %d", s.bottom)
	}
	if s.stack[0] != 5 {
		t.Errorf("Expected value 5, got %d", s.stack[0])
	}
	
	// Push second element
	s.Push(10)
	if s.size != 2 {
		t.Errorf("Expected size 2, got %d", s.size)
	}
	if s.top != 1 {
		t.Errorf("Expected top 1, got %d", s.top)
	}
	if s.stack[1] != 10 {
		t.Errorf("Expected value 10, got %d", s.stack[1])
	}
}

func TestPop(t *testing.T) {
	s := New()
	
	// Pop from empty stack
	val := s.Pop()
	if val != 0 {
		t.Errorf("Expected 0 from empty stack, got %d", val)
	}
	
	// Push and pop
	s.Push(5)
	s.Push(10)
	
	val = s.Pop()
	if val != 10 {
		t.Errorf("Expected 10, got %d", val)
	}
	if s.Size() != 1 {
		t.Errorf("Expected size 1, got %d", s.Size())
	}
	if s.top != 0 {
		t.Errorf("Expected top 0, got %d", s.top)
	}
	
	val = s.Pop()
	if val != 5 {
		t.Errorf("Expected 5, got %d", val)
	}
	if s.Size() != 0 {
		t.Errorf("Expected size 0, got %d", s.Size())
	}
}

func TestPeek(t *testing.T) {
	s := New()
	
	// Peek from empty stack
	val := s.Peek()
	if val != 0 {
		t.Errorf("Expected 0 from empty stack, got %d", val)
	}
	
	// Push and peek
	s.Push(5)
	val = s.Peek()
	if val != 5 {
		t.Errorf("Expected 5, got %d", val)
	}
	
	// Peek should not change size
	if s.size != 1 {
		t.Errorf("Expected size 1, got %d", s.size)
	}
}

func TestIsEmpty(t *testing.T) {
	s := New()
	
	if !s.IsEmpty() {
		t.Error("New stack should be empty")
	}
	
	s.Push(5)
	if s.IsEmpty() {
		t.Error("Stack with elements should not be empty")
	}
	
	s.Pop()
	if !s.IsEmpty() {
		t.Error("Stack after pop should be empty")
	}
}

func TestSize(t *testing.T) {
	s := New()
	
	if s.Size() != 0 {
		t.Errorf("Expected size 0, got %d", s.Size())
	}
	
	s.Push(5)
	if s.Size() != 1 {
		t.Errorf("Expected size 1, got %d", s.Size())
	}
	
	s.Push(10)
	if s.Size() != 2 {
		t.Errorf("Expected size 2, got %d", s.Size())
	}
	
	s.Pop()
	if s.Size() != 1 {
		t.Errorf("Expected size 1, got %d", s.Size())
	}
}

func TestToSlice(t *testing.T) {
	s := New()
	
	// Empty stack
	slice := s.ToSlice()
	if len(slice) != 0 {
		t.Error("Empty stack should return empty slice")
	}
	
	// Stack with elements using FromSlice (like C implementation)
	values := []int{3, 1, 4}
	s = FromSlice(values)
	
	slice = s.ToSlice()
	expected := []int{3, 1, 4}
	if !reflect.DeepEqual(slice, expected) {
		t.Errorf("Expected %v, got %v", expected, slice)
	}
}

func TestFromSlice(t *testing.T) {
	values := []int{3, 1, 4, 1, 5}
	s := FromSlice(values)
	
	if s.Size() != len(values) {
		t.Errorf("Expected size %d, got %d", len(values), s.Size())
	}
	
	// Check order (first element should be on top)
	if s.Peek() != values[0] {
		t.Errorf("Expected top value %d, got %d", values[0], s.Peek())
	}
}

func TestGetValueAtPosition(t *testing.T) {
	// Create stack using FromSlice (like C implementation)
	values := []int{3, 1, 4}
	s := FromSlice(values)
	
	// Test 1-based indexing
	if s.GetValueAtPosition(1) != 3 {
		t.Error("Position 1 should return first element")
	}
	if s.GetValueAtPosition(2) != 1 {
		t.Error("Position 2 should return second element")
	}
	if s.GetValueAtPosition(3) != 4 {
		t.Error("Position 3 should return third element")
	}
	
	// Test out of bounds
	if s.GetValueAtPosition(0) != 0 {
		t.Error("Position 0 should return 0")
	}
	if s.GetValueAtPosition(4) != 0 {
		t.Error("Position 4 should return 0")
	}
}

func TestGetValueAtPosition0(t *testing.T) {
	// Create stack using FromSlice (like C implementation)
	values := []int{3, 1, 4}
	s := FromSlice(values)
	
	// Test 0-based indexing
	if s.GetValueAtPosition0(0) != 3 {
		t.Error("Position 0 should return first element")
	}
	if s.GetValueAtPosition0(1) != 1 {
		t.Error("Position 1 should return second element")
	}
	if s.GetValueAtPosition0(2) != 4 {
		t.Error("Position 2 should return third element")
	}
	
	// Test out of bounds
	if s.GetValueAtPosition0(-1) != 0 {
		t.Error("Position -1 should return 0")
	}
	if s.GetValueAtPosition0(3) != 0 {
		t.Error("Position 3 should return 0")
	}
}

func TestIsFull(t *testing.T) {
	s := New()
	
	if s.IsFull() {
		t.Error("Empty stack should not be full")
	}
	
	// Stack created with FromSlice should be full (like C implementation)
	values := []int{5}
	s = FromSlice(values)
	if !s.IsFull() {
		t.Error("Stack created with FromSlice should be full (like C implementation)")
	}
}

func TestCurrentSize(t *testing.T) {
	s := New()
	
	if s.CurrentSize() != 0 {
		t.Errorf("Expected current size 0, got %d", s.CurrentSize())
	}
	
	s.Push(5)
	if s.CurrentSize() != 1 {
		t.Errorf("Expected current size 1, got %d", s.CurrentSize())
	}
	
	s.Push(10)
	if s.CurrentSize() != 2 {
		t.Errorf("Expected current size 2, got %d", s.CurrentSize())
	}
}

func TestNextUp(t *testing.T) {
	// Create stack using FromSlice (like C implementation)
	values := []int{1, 2, 3}
	s := FromSlice(values)
	
	// Test next up from various positions
	// With exact capacity allocation (size = 3), NextUp(0) = 2
	if s.NextUp(0) != 2 {
		t.Errorf("NextUp(0) should return 2, got %d", s.NextUp(0))
	}
	if s.NextUp(1) != 0 {
		t.Errorf("NextUp(1) should return 0, got %d", s.NextUp(1))
	}
	if s.NextUp(2) != 1 {
		t.Errorf("NextUp(2) should return 1, got %d", s.NextUp(2))
	}
}

func TestNextDown(t *testing.T) {
	// Create stack using FromSlice (like C implementation)
	values := []int{1, 2, 3}
	s := FromSlice(values)
	
	// Test next down from various positions
	if s.NextDown(0) != 1 {
		t.Errorf("NextDown(0) should return 1, got %d", s.NextDown(0))
	}
	if s.NextDown(1) != 2 {
		t.Errorf("NextDown(1) should return 2, got %d", s.NextDown(1))
	}
	if s.NextDown(2) != 0 {
		t.Errorf("NextDown(2) should return 0 (wrap around), got %d", s.NextDown(2))
	}
}

func TestValue(t *testing.T) {
	// Create stack using FromSlice (like C implementation)
	values := []int{1, 2, 3}
	s := FromSlice(values)
	
	// Test valid indices
	if s.Value(0) != 1 {
		t.Error("Value(0) should return 1")
	}
	if s.Value(1) != 2 {
		t.Error("Value(1) should return 2")
	}
	if s.Value(2) != 3 {
		t.Error("Value(2) should return 3")
	}
	
	// Test out of bounds
	if s.Value(-1) != 0 {
		t.Error("Value(-1) should return 0")
	}
	if s.Value(3) != 0 {
		t.Error("Value(3) should return 0")
	}
}

func TestSetValue(t *testing.T) {
	s := New()
	s.Push(1)
	s.Push(2)
	s.Push(3)
	
	// Test valid set
	if !s.SetValue(1, 99) {
		t.Error("SetValue should succeed for valid index")
	}
	if s.Value(1) != 99 {
		t.Error("SetValue should actually set the value")
	}
	
	// Test invalid set
	if s.SetValue(-1, 99) {
		t.Error("SetValue should fail for negative index")
	}
	if s.SetValue(3, 99) {
		t.Error("SetValue should fail for out of bounds index")
	}
}
