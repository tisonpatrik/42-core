package ops

import (
	"push_swap_prototype/internal/stack"
	"testing"
)

func snapshotStack(s *stack.Stack) (size int, top, bottom int, values []int) {
    size = stack.GetSize(s)
    top = stack.GetTop(s)
    bottom = stack.GetBottom(s)
    values = make([]int, size)
    for i := 0; i < size; i++ {
        values[i] = stack.GetValue(s, i)
    }
    return
}

func equalSlices(a, b []int) bool {
    if len(a) != len(b) { return false }
    for i := range a {
        if a[i] != b[i] {
            return false
        }
    }
    return true
}

// No-op: B is empty
// Arrange: A has a few values, B is empty; save the original lengths and contents of A/B, and the number of logged operations.
// Act: Call pa.
// Assert: pa returns failure/false; lengths of A and B remain unchanged; contents remain unchanged; no operations are added to the log.
func TestPushAEmptySource(t *testing.T) {
    // Arrange
    numbers := []int{1, 2, 3, 4, 5}
    ps := InitData(numbers) // předpoklad: A naplněná z 'numbers', B prázdná nebo ne?

    // Udělej B explicitně prázdné
    ps.B = stack.InitStack(len(numbers))

    // snapshot před
    sizeA0, topA0, botA0, valsA0 := snapshotStack(ps.A)
    sizeB0, topB0, botB0, valsB0 := snapshotStack(ps.B)
    opCount0 := len(ps.OpList)

    // Act
    PushA(ps) // expect false (no-op)

    // Assert – sizes remain unchanged
    sizeA1, topA1, botA1, valsA1 := snapshotStack(ps.A)
    sizeB1, topB1, botB1, valsB1 := snapshotStack(ps.B)
    opCount1 := len(ps.OpList)

    if sizeA1 != sizeA0 {
        t.Errorf("Expected stack A size to remain %d, got %d", sizeA0, sizeA1)
    }
    if sizeB1 != sizeB0 {
        t.Errorf("Expected stack B size to remain %d, got %d", sizeB0, sizeB1)
    }

    // Assert – contents remain unchanged
    if !equalSlices(valsA1, valsA0) {
        t.Errorf("Expected stack A contents to remain %v, got %v", valsA0, valsA1)
    }
    if !equalSlices(valsB1, valsB0) {
        t.Errorf("Expected stack B contents to remain %v, got %v", valsB0, valsB1)
    }

    // (Optional) – pointers remain unchanged
    if topA1 != topA0 || botA1 != botA0 {
        t.Errorf("Expected A top/bottom to remain (%d,%d), got (%d,%d)", topA0, botA0, topA1, botA1)
    }
    if topB1 != topB0 || botB1 != botB0 {
        t.Errorf("Expected B top/bottom to remain (%d,%d), got (%d,%d)", topB0, botB0, topB1, botB1)
    }

    // Log – no new operations
    if opCount1 != opCount0 {
        t.Errorf("Expected operation count to remain %d, got %d", opCount0, opCount1)
    }
}

// Basic: push from B to empty A
// Arrange: A empty; B has one element x on top.
// Act: pa.
// Assert: A has length 1 and top = x; B is empty; exactly one operation pa is logged.
func TestPushAFromBToEmptyA(t *testing.T) {
	// Arrange
	ps := InitData([]int{})
	ps.A = stack.InitStack(1) // Empty stack A
	ps.B = stack.InitStack(1)
	stack.Push(ps.B, 42) // Single element x = 42
	
	initialSizeA := stack.GetSize(ps.A)
	initialSizeB := stack.GetSize(ps.B)
	initialOpCount := len(ps.OpList)
	
	t.Logf("Initial sizes: A=%d, B=%d, OpCount=%d", initialSizeA, initialSizeB, initialOpCount)
	
	// Act
	PushA(ps)
	
	// Assert
	finalSizeA := stack.GetSize(ps.A)
	finalSizeB := stack.GetSize(ps.B)
	finalOpCount := len(ps.OpList)
	
	t.Logf("Final sizes: A=%d, B=%d, OpCount=%d", finalSizeA, finalSizeB, finalOpCount)
	
	if finalSizeA != 1 {
		t.Errorf("Expected stack A size to be 1, got %d", finalSizeA)
	}
	if finalSizeB != 0 {
		t.Errorf("Expected stack B size to be 0, got %d", finalSizeB)
	}
	if finalOpCount != initialOpCount+1 {
		t.Errorf("Expected operation count to increase by 1, got %d", finalOpCount)
	}
	
	// Check that A now contains the value from B
	topValue := stack.Peek(ps.A)
	if topValue == nil || *topValue != 42 {
		t.Errorf("Expected stack A top to be 42, got %v", topValue)
	}
}

// Push to non-empty A
// Arrange: A contains [a_top, …]; B has x on top.
// Act: pa.
// Assert: Top of A is x, below it was a_top; lengths: A+1, B-1; log contains pa.
func TestPushAToNonEmptyA(t *testing.T) {
	// Arrange
	ps := InitData([]int{})
	ps.A = stack.InitStack(5)
	ps.B = stack.InitStack(5)
	
	// Fill A with some values: [10, 20, 30] (top to bottom)
	stack.Push(ps.A, 30)
	stack.Push(ps.A, 20)
	stack.Push(ps.A, 10)
	
	// Put x = 42 on top of B
	stack.Push(ps.B, 42)
	
	initialSizeA := stack.GetSize(ps.A)
	initialSizeB := stack.GetSize(ps.B)
	initialOpCount := len(ps.OpList)
	
	// Act
	PushA(ps)
	
	// Assert
	finalSizeA := stack.GetSize(ps.A)
	finalSizeB := stack.GetSize(ps.B)
	finalOpCount := len(ps.OpList)
	
	// Check lengths: A+1, B-1
	if finalSizeA != initialSizeA+1 {
		t.Errorf("Expected stack A size to be %d+1=%d, got %d", initialSizeA, initialSizeA+1, finalSizeA)
	}
	if finalSizeB != initialSizeB-1 {
		t.Errorf("Expected stack B size to be %d-1=%d, got %d", initialSizeB, initialSizeB-1, finalSizeB)
	}
	
	// Check operation count increased by 1
	if finalOpCount != initialOpCount+1 {
		t.Errorf("Expected operation count to increase by 1, got %d", finalOpCount)
	}
	
	// Check that A top is now x (42)
	topValue := stack.Peek(ps.A)
	if topValue == nil || *topValue != 42 {
		t.Errorf("Expected stack A top to be 42, got %v", topValue)
	}
	
	// Check that the second element is the former a_top (10)
	secondValue := stack.GetValue(ps.A, 1)
	if secondValue != 10 {
		t.Errorf("Expected stack A second element to be 10 (former top), got %d", secondValue)
	}
}


func TestPushAMultipleOperations(t *testing.T) {
    // Arrange
    ps := InitData([]int{})
    ps.A = stack.InitStack(3) // Empty stack A
    ps.B = stack.InitStack(3) // Empty stack B

    // B (from top): [b1, b2]  => po dvou pa bude A: top=b2, pod n�m b1
    // Aby byl top=b1, nejd\u0159�v pushni b2, potom b1:
    b1, b2 := 100, 50
    stack.Push(ps.B, b2) // nyn� B: [50]
    stack.Push(ps.B, b1) // nyn� B: [100 (top), 50]

    initialSizeA := stack.GetSize(ps.A)
    initialSizeB := stack.GetSize(ps.B)
    initialOpCount := len(ps.OpList)

    t.Logf("Initial sizes: A=%d, B=%d, OpCount=%d", initialSizeA, initialSizeB, initialOpCount)

    // Act: pa, pa
    PushA(ps)
    midSizeA := stack.GetSize(ps.A)
    midSizeB := stack.GetSize(ps.B)
    midOpCount := len(ps.OpList)
    t.Logf("After first pa: A=%d, B=%d, OpCount=%d", midSizeA, midSizeB, midOpCount)

    PushA(ps)

    // Assert
    finalSizeA := stack.GetSize(ps.A)
    finalSizeB := stack.GetSize(ps.B)
    finalOpCount := len(ps.OpList)

    t.Logf("Final sizes: A=%d, B=%d, OpCount=%d", finalSizeA, finalSizeB, finalOpCount)

    // A m� 2 prvky, B pr�zdn�
    if finalSizeA != 2 {
        t.Errorf("Expected stack A size to be 2, got %d", finalSizeA)
    }
    if finalSizeB != 0 {
        t.Errorf("Expected stack B size to be 0, got %d", finalSizeB)
    }

    // OpList narostl o 2
    if finalOpCount != initialOpCount+2 {
        t.Errorf("Expected operation count to increase by 2, got %d", finalOpCount)
    }

    // LIFO po\u0159ad�: A top = b2, pod n�m b1
    topPtr := stack.Peek(ps.A)
    if topPtr == nil {
        t.Fatalf("Expected non-nil top after two pa")
    }
    if *topPtr != b2 {
        t.Errorf("Expected stack A top to be %d (b2), got %d", b2, *topPtr)
    }

    second := stack.GetValue(ps.A, 1)
    if second != b1 {
        t.Errorf("Expected stack A second element to be %d (b1), got %d", b1, second)
    }

    // Log: ["pa","pa"]
    if len(ps.OpList) != 2 {
        t.Errorf("Expected 2 operations in log, got %d", len(ps.OpList))
    }
    for i, op := range ps.OpList {
        if op != PA {
            t.Errorf("Expected operation %d to be PA, got %v", i, op)
        }
    }
}
