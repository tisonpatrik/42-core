package stack

import (
	"testing"
)

// TestInitStack tests stack initialization
func TestInitStack(t *testing.T) {
	// Arrange
	size := 5
	
	// Act
	stack := InitStack(size)
	
	// Assert
	if stack.capacity != size {
		t.Errorf("Expected capacity %d, got %d", size, stack.capacity)
	}
	if stack.top != 0 {
		t.Errorf("Expected Top to be 0, got %d", stack.top)
	}
	if stack.bottom != -1 {
		t.Errorf("Expected Bottom to be -1 (empty), got %d", stack.bottom)
	}
	if len(stack.stack) != size {
		t.Errorf("Expected stack slice length %d, got %d", size, len(stack.stack))
	}
	
	// Check all values are initialized to nullValue
	for i, val := range stack.stack {
		if val != nullValue {
			t.Errorf("Expected stack[%d] to be %d, got %d", i, nullValue, val)
		}
	}
}

// TestPushToEmptyStack tests pushing to an empty stack
func TestPushToEmptyStack(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	
	// Act
	Push(stack, 1)
	
	// Assert
	if stack.top != 0 {
		t.Errorf("Expected Top to be 0, got %d", stack.top)
	}
	if stack.bottom != 0 {
		t.Errorf("Expected Bottom to be 0, got %d", stack.bottom)
	}
	if stack.stack[0] != 1 {
		t.Errorf("Expected stack[0] to be 1, got %d", stack.stack[0])
	}
	if GettSize(stack) != 1 {
		t.Errorf("Expected size 1, got %d", GettSize(stack))
	}
}

// TestPushMultipleElements tests pushing multiple elements
func TestPushMultipleElements(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	
	// Act
	Push(stack, 1)
	Push(stack, 2)
	Push(stack, 3)
	
	// Assert
	// In circular buffer: Top moves up (decreases) with each push
	// First push: Top = 0, stores at index 0
	// Second push: Top = 2 (NextUp(0) = 2), stores at index 2
	// Third push: Top = 1 (NextUp(2) = 1), stores at index 1
	if stack.top != 1 {
		t.Errorf("Expected Top to be 1, got %d", stack.top)
	}
	if stack.bottom != 0 {
		t.Errorf("Expected Bottom to be 0, got %d", stack.bottom)
	}
	if GettSize(stack) != 3 {
		t.Errorf("Expected size 3, got %d", GettSize(stack))
	}
	
	// Check values are stored in circular buffer order
	// Index 0: 1 (first push)
	// Index 2: 2 (second push) 
	// Index 1: 3 (third push)
	if stack.stack[0] != 1 {
		t.Errorf("Expected stack[0] to be 1, got %d", stack.stack[0])
	}
	if stack.stack[2] != 2 {
		t.Errorf("Expected stack[2] to be 2, got %d", stack.stack[2])
	}
	if stack.stack[1] != 3 {
		t.Errorf("Expected stack[1] to be 3, got %d", stack.stack[1])
	}
}

// TestPushWithWrapping tests push behavior with wrapping
func TestPushWithWrapping(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	
	// Fill the stack
	Push(stack, 1)
	Push(stack, 2)
	Push(stack, 3)
	
	// Pop one element to create space
	Pop(stack)
	
	// Act
	// Push new element (should wrap around)
	Push(stack, 4)
	
	// Assert
	// After pop, Top was at 1, so NextUp(1) = 0
	// But actually: Pop() moves Top to NextDown(1) = 2, then Push moves Top to NextUp(2) = 1
	if stack.top != 1 {
		t.Errorf("Expected Top to be 1, got %d", stack.top)
	}
	if stack.stack[1] != 4 {
		t.Errorf("Expected stack[1] to be 4, got %d", stack.stack[1])
	}
	if GettSize(stack) != 3 {
		t.Errorf("Expected size 3, got %d", GettSize(stack))
	}
}

// TestPopFromEmptyStack tests popping from an empty stack
func TestPopFromEmptyStack(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	
	// Act
	value := Pop(stack)
	
	// Assert
	if value != nullValue {
		t.Errorf("Expected nullValue (%d), got %d", nullValue, value)
	}
	if stack.top != 0 {
		t.Errorf("Expected Top to remain 0, got %d", stack.top)
	}
	if stack.bottom != -1 {
		t.Errorf("Expected Bottom to remain -1, got %d", stack.bottom)
	}
}

// TestPopSingleElement tests popping a single element
func TestPopSingleElement(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	Push(stack, 1)
	
	// Act
	value := Pop(stack)
	
	// Assert
	if value != 1 {
		t.Errorf("Expected value 1, got %d", value)
	}
	if stack.top != 0 {
		t.Errorf("Expected Top to be 0, got %d", stack.top)
	}
	if stack.bottom != -1 {
		t.Errorf("Expected Bottom to be -1 (empty), got %d", stack.bottom)
	}
	if stack.stack[0] != nullValue {
		t.Errorf("Expected stack[0] to be %d, got %d", nullValue, stack.stack[0])
	}
}

// TestPopMultipleElements tests popping multiple elements
func TestPopMultipleElements(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	Push(stack, 1)
	Push(stack, 2)
	Push(stack, 3)
	
	// Act & Assert
	// Pop in reverse order (LIFO)
	// Top is at index 1, so we pop from there first
	values := []int{3, 2, 1}
	for _, expected := range values {
		value := Pop(stack)
		if value != expected {
			t.Errorf("Expected value %d, got %d", expected, value)
		}
	}
	
	// Stack should be empty
	if GettSize(stack) != 0 {
		t.Errorf("Expected size 0, got %d", GettSize(stack))
	}
	if stack.bottom != -1 {
		t.Errorf("Expected Bottom to be -1, got %d", stack.bottom)
	}
}

// TestPeekEmptyStack tests peeking at an empty stack
func TestPeekEmptyStack(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	
	// Act
	value := Peek(stack)
	
	// Assert
	if value != nil {
		t.Errorf("Expected nil, got %v", value)
	}
}

// TestPeekNonEmptyStack tests peeking at a non-empty stack
func TestPeekNonEmptyStack(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	Push(stack, 1)
	Push(stack, 2)
	
	// Act
	value := Peek(stack)
	
	// Assert
	if value == nil {
		t.Error("Expected non-nil value")
	} else if *value != 2 {
		t.Errorf("Expected value 2, got %d", *value)
	}
	
	// Peeking shouldn't change the stack
	if GettSize(stack) != 2 {
		t.Errorf("Expected size to remain 2, got %d", GettSize(stack))
	}
}

// TestSingleElementOperations tests single element stack operations
func TestSingleElementOperations(t *testing.T) {
	// Arrange
	stack := InitStack(1)
	
	// Act
	// Push single element
	Push(stack, 1)
	
	// Assert
	if !IsFull(stack) {
		t.Error("Expected single element stack to be full")
	}
	
	// Try to push when full
	defer func() {
		if r := recover(); r == nil {
			t.Error("Expected panic when pushing to full stack")
		}
	}()
	Push(stack, 2)
}

// TestWrappingBehavior tests wrapping behavior
func TestWrappingBehavior(t *testing.T) {
	// Arrange
	stack := InitStack(2)
	
	// Act & Assert
	// Fill and empty multiple times to test wrapping
	for i := 0; i < 3; i++ {
		Push(stack, 1)
		Push(stack, 2)
		
		if GettSize(stack) != 2 {
			t.Errorf("Expected size 2, got %d", GettSize(stack))
		}
		
		Pop(stack)
		Pop(stack)
		
		if GettSize(stack) != 0 {
			t.Errorf("Expected size 0, got %d", GettSize(stack))
		}
	}
}

// TestPanicPushToFullStack tests panic when pushing to full stack
func TestPanicPushToFullStack(t *testing.T) {
	// Arrange
	stack := InitStack(1)
	Push(stack, 1)
	
	// Act & Assert
	defer func() {
		if r := recover(); r == nil {
			t.Error("Expected panic when pushing to full stack")
		}
	}()
	Push(stack, 2)
}

// TestPanicPushNegativeValue tests panic when pushing negative value
func TestPanicPushNegativeValue(t *testing.T) {
	// Arrange
	stack := InitStack(3)
	
	// Act & Assert
	defer func() {
		if r := recover(); r == nil {
			t.Error("Expected panic when pushing negative value")
		}
	}()
	Push(stack, -1)
}
