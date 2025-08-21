package operations

import (
	"push_swap_prototype/internal/stack"
	"reflect"
	"testing"
)

// TestPush_aEmptySource tests Push_a with empty source stack B (should do nothing but record operation)
func TestPush_aEmptySource(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2}) // stack A has elements
	ps.B = stack.New() // stack B is empty
	Push_a(ps)
	if ps.A.CurrentSize() != 2 {
		t.Error("Stack A should not change when source B is empty")
	}
	if ps.B.CurrentSize() != 0 {
		t.Error("Stack B should remain empty")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != PA {
		t.Errorf("Expected PA operation, got %v", ps.OpList[0])
	}
}

// TestPush_aSingleElementSource tests Push_a with single element in source stack B
func TestPush_aSingleElementSource(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(3) // capacity for 3 elements
	ps.A.FillFromSlice([]int{1, 2}) // stack A: [1, 2] - not full, has capacity 3
	ps.B.FillFromSlice([]int{42}) // stack B: [42] - not full, has capacity 3
	Push_a(ps)
	// Since stack A has capacity, the push should succeed
	expectedA := []int{42, 1, 2} // after successful push: [42, 1, 2]
	expectedB := []int{} // after successful push: empty
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
	if ps.OpList[0] != PA {
		t.Errorf("Expected PA operation, got %v", ps.OpList[0])
	}
}

// TestPush_aMultipleElementsSource tests Push_a with multiple elements in source stack B
func TestPush_aMultipleElementsSource(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(5) // capacity for 5 elements total
	ps.A.FillFromSlice([]int{1, 2}) // stack A: [1, 2] - not full, has capacity 5
	ps.B.FillFromSlice([]int{5, 4, 3}) // stack B: [5, 4, 3] - not full, has capacity 5
	Push_a(ps)
	// Since stack A now has capacity, the push should succeed
	expectedA := []int{5, 1, 2} // after successful push: [5, 1, 2] (only top element moved)
	expectedB := []int{4, 3} // after successful push: [4, 3] (top element removed)
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
	if ps.OpList[0] != PA {
		t.Errorf("Expected PA operation, got %v", ps.OpList[0])
	}
}

// TestPush_aSuccessfulPush tests Push_a when destination stack A is not full
func TestPush_aSuccessfulPush(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(2) // capacity for 2 elements
	ps.A.FillFromSlice([]int{1}) // stack A: [1] - not full, has capacity 2
	ps.B.FillFromSlice([]int{42}) // stack B: [42] - not full, has capacity 2
	Push_a(ps)
	// Since stack A is not full, the push should succeed
	expectedA := []int{42, 1} // after successful push: [42, 1]
	expectedB := []int{} // after successful push: empty
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
	if ps.OpList[0] != PA {
		t.Errorf("Expected PA operation, got %v", ps.OpList[0])
	}
}

// TestPush_bEmptySource tests Push_b with empty source stack A (should do nothing but record operation)
func TestPush_bEmptySource(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.New() // stack A is empty
	ps.B = stack.FromSlice([]int{3, 4}) // stack B has elements
	Push_b(ps)
	if ps.A.CurrentSize() != 0 {
		t.Error("Stack A should remain empty when source A is empty")
	}
	if ps.B.CurrentSize() != 2 {
		t.Error("Stack B should not change when source A is empty")
	}
	if len(ps.OpList) != 1 {
		t.Errorf("Expected 1 operation, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != PB {
		t.Errorf("Expected PB operation, got %v", ps.OpList[0])
	}
}

// TestPush_bSingleElementSource tests Push_b with single element in source stack A
func TestPush_bSingleElementSource(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(3) // capacity for 3 elements
	ps.A.FillFromSlice([]int{42}) // stack A: [42] - not full, has capacity 3
	ps.B.FillFromSlice([]int{3, 4}) // stack B: [3, 4] - not full, has capacity 3
	Push_b(ps)
	// Since stack B now has capacity, the push should succeed
	expectedA := []int{} // after successful push: empty
	expectedB := []int{42, 3, 4} // after successful push: [42, 3, 4]
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
	if ps.OpList[0] != PB {
		t.Errorf("Expected PB operation, got %v", ps.OpList[0])
	}
}

// TestPush_bMultipleElementsSource tests Push_b with multiple elements in source stack A
func TestPush_bMultipleElementsSource(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(5) // capacity for 5 elements total
	ps.A.FillFromSlice([]int{5, 4, 3}) // stack A: [5, 4, 3] - not full, has capacity 5
	ps.B.FillFromSlice([]int{1, 2}) // stack B: [1, 2] - not full, has capacity 5
	Push_b(ps)
	// Since stack B now has capacity, the push should succeed
	expectedA := []int{4, 3} // after successful push: [4, 3] (top element removed)
	expectedB := []int{5, 1, 2} // after successful push: [5, 1, 2] (top element moved)
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
	if ps.OpList[0] != PB {
		t.Errorf("Expected PB operation, got %v", ps.OpList[0])
	}
}

// TestPush_bSuccessfulPush tests Push_b when destination stack B is not full
func TestPush_bSuccessfulPush(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(2) // capacity for 2 elements
	ps.A.FillFromSlice([]int{42}) // stack A: [42] - not full, has capacity 2
	ps.B.FillFromSlice([]int{3}) // stack B: [3] - not full, has capacity 2
	Push_b(ps)
	// Since stack B is not full, the push should succeed
	expectedA := []int{} // after successful push: empty
	expectedB := []int{42, 3} // after successful push: [42, 3]
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
	if ps.OpList[0] != PB {
		t.Errorf("Expected PB operation, got %v", ps.OpList[0])
	}
}

// TestPush_aEmptyDestination tests Push_a with empty destination stack A
func TestPush_aEmptyDestination(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.New() // stack A is empty
	ps.B = stack.FromSlice([]int{42}) // stack B: [42]
	Push_a(ps)
	expectedA := []int{42} // after push: [42]
	expectedB := []int{} // after push: empty
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
	if ps.OpList[0] != PA {
		t.Errorf("Expected PA operation, got %v", ps.OpList[0])
	}
}

// TestPush_aWritingModeDisabled tests Push_a with writing mode disabled
func TestPush_aWritingModeDisabled(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(3) // capacity for 3 elements
	ps.WritingMode = false
	ps.A.FillFromSlice([]int{1, 2}) // stack A: [1, 2] - not full, has capacity 3
	ps.B.FillFromSlice([]int{42}) // stack B: [42] - not full, has capacity 3
	Push_a(ps)
	// Since stack A now has capacity, the push should succeed
	expectedA := []int{42, 1, 2} // after successful push: [42, 1, 2]
	expectedB := []int{} // after successful push: empty
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

// TestPush_bEmptyDestination tests Push_b with empty destination stack B
func TestPush_bEmptyDestination(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{42}) // stack A: [42]
	ps.B = stack.New() // stack B is empty
	Push_b(ps)
	expectedA := []int{} // after push: empty
	expectedB := []int{42} // after push: [42]
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
	if ps.OpList[0] != PB {
		t.Errorf("Expected PB operation, got %v", ps.OpList[0])
	}
}

// TestPush_bWritingModeDisabled tests Push_b with writing mode disabled
func TestPush_bWritingModeDisabled(t *testing.T) {
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(3) // capacity for 3 elements
	ps.WritingMode = false
	ps.A.FillFromSlice([]int{42}) // stack A: [42] - not full, has capacity 3
	ps.B.FillFromSlice([]int{3, 4}) // stack B: [3, 4] - not full, has capacity 3
	Push_b(ps)
	// Since stack B now has capacity, the push should succeed
	expectedA := []int{} // after successful push: empty
	expectedB := []int{42, 3, 4} // after successful push: [42, 3, 4]
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

// TestPushBothStacksEmpty tests push operations when both stacks are empty
func TestPushBothStacksEmpty(t *testing.T) {
	ps := NewPushSwapData()
	// Both stacks are empty
	Push_a(ps)
	Push_b(ps)
	if ps.A.CurrentSize() != 0 || ps.B.CurrentSize() != 0 {
		t.Error("Both stacks should remain empty")
	}
	if len(ps.OpList) != 2 {
		t.Errorf("Expected 2 operations, got %d", len(ps.OpList))
	}
	if ps.OpList[0] != PA {
		t.Errorf("Expected first operation PA, got %v", ps.OpList[0])
	}
	if ps.OpList[1] != PB {
		t.Errorf("Expected second operation PB, got %v", ps.OpList[1])
	}
}

// TestPushMultipleOperations tests multiple push operations in sequence
func TestPushMultipleOperations(t *testing.T) {
	ps := NewPushSwapData()
	ps.A = stack.FromSlice([]int{1, 2, 3}) // A: [1, 2, 3]
	ps.B = stack.New() // B: empty
	
	// Push first element from A to B
	Push_b(ps)
	expectedA := []int{2, 3}
	expectedB := []int{1}
	resultA := ps.A.ToSlice()
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("After first push: Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("After first push: Expected B %v, got %v", expectedB, resultB)
	}
	
	// Push second element from A to B
	Push_b(ps)
	expectedA = []int{3}
	expectedB = []int{2, 1}
	resultA = ps.A.ToSlice()
	resultB = ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("After second push: Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("After second push: Expected B %v, got %v", expectedB, resultB)
	}
	
	// Push back from B to A
	Push_a(ps)
	expectedA = []int{2, 3}
	expectedB = []int{1}
	resultA = ps.A.ToSlice()
	resultB = ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("After push back: Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("After push back: Expected B %v, got %v", expectedB, resultB)
	}
	
	if len(ps.OpList) != 3 {
		t.Errorf("Expected 3 operations, got %d", len(ps.OpList))
	}
}

// TestPushCLikeBehavior tests that Go implementation behaves exactly like C implementation
func TestPushCLikeBehavior(t *testing.T) {
	// C implementation doesn't check if source is empty
	// It just assumes there are elements and performs the operation
	// This test verifies our Go implementation matches this behavior
	
	// Create data structure like C init_data: both stacks get same capacity
	ps := NewPushSwapDataWithCapacity(3) // capacity for 3 elements
	
	// Test with empty source - C would just do nothing
	ps.A.FillFromSlice([]int{1, 2}) // stack A: [1, 2] - not full, has capacity 3
	// ps.B remains empty but has capacity 3
	Push_a(ps)
	// In C, this would just do nothing, but our Go implementation
	// should handle it gracefully and record the operation
	if ps.A.CurrentSize() != 2 {
		t.Error("Stack A should not change when source B is empty")
	}
	if ps.B.CurrentSize() != 0 {
		t.Error("Stack B should remain empty")
	}
	
	// Test with valid source and destination - now destination has capacity
	ps.B.FillFromSlice([]int{42}) // stack B: [42] - not full, has capacity 3
	Push_a(ps)
	// Since stack A now has capacity, the push should succeed
	expectedA := []int{42, 1, 2} // after successful push: [42, 1, 2]
	expectedB := []int{} // after successful push: empty
	resultA := ps.A.ToSlice()
	resultB := ps.B.ToSlice()
	if !reflect.DeepEqual(resultA, expectedA) {
		t.Errorf("Expected A %v, got %v", expectedA, resultA)
	}
	if !reflect.DeepEqual(resultB, expectedB) {
		t.Errorf("Expected B %v, got %v", expectedB, resultB)
	}
}
