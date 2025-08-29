package solver

import (
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
	"testing"
)

func TestSortThreeAlreadySorted(t *testing.T) {
	// Arrange
	input := []int{1, 2, 3}
	expected := []int{1, 2, 3}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeReverseSorted(t *testing.T) {
	// Arrange
	input := []int{3, 2, 1}
	expected := []int{1, 2, 3}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeFirstTwoSwapped(t *testing.T) {
	// Arrange
	input := []int{2, 1, 3}
	expected := []int{1, 2, 3}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeLastTwoSwapped(t *testing.T) {
	// Arrange
	input := []int{1, 3, 2}
	expected := []int{1, 2, 3}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeFirstAndLastSwapped(t *testing.T) {
	// Arrange
	input := []int{3, 1, 2}
	expected := []int{1, 2, 3}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeMiddleAndLastSwapped(t *testing.T) {
	// Arrange
	input := []int{2, 3, 1}
	expected := []int{1, 2, 3}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeEmptyStack(t *testing.T) {
	// Arrange
	input := []int{}
	expected := []int{}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeSingleElement(t *testing.T) {
	// Arrange
	input := []int{5}
	expected := []int{5}
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

func TestSortThreeTwoElements(t *testing.T) {
	// Arrange
	input := []int{2, 1}
	expected := []int{2, 1} // Should not be modified
	ps := ops.InitData(input)

	// Act
	SortThree(ps)

	// Assert
	if !isStackSorted(ps.A, expected) {
		t.Errorf("SortThree() failed for %v, got %v, want %v", 
			input, stackToString(ps.A), expected)
	}
}

// Helper function to check if stack matches expected order
func isStackSorted(s *stack.Stack, expected []int) bool {
	if stack.GetSize(s) != len(expected) {
		return false
	}
	
	current := stack.GetHead(s)
	for _, expectedVal := range expected {
		if current == nil || current.GetContent() != expectedVal {
			return false
		}
		current = current.GetNext()
	}
	return true
}

// Helper function to convert stack to string for debugging
func stackToString(s *stack.Stack) string {
	if stack.IsEmpty(s) {
		return "[]"
	}
	
	result := "["
	current := stack.GetHead(s)
	for current != nil {
		if result != "[" {
			result += ","
		}
		result += string(rune(current.GetContent() + '0'))
		current = current.GetNext()
	}
	result += "]"
	return result
}
