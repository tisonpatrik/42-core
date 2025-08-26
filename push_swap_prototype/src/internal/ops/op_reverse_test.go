package ops

import (
	"testing"

	"push_swap_prototype/internal/stack"
)

// ReverseRotateA: pr�zdn� zdroj -> no-op (bez logu)
func TestReverseRotateA_Empty_NoOp(t *testing.T) {
	ps := newState(3, 3) // A empty
	ReverseRotateA(ps)
	if got := stack.GetSize(ps.A); got != 0 {
		t.Fatalf("expected A size 0, got %d", got)
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %v", ps.OpList)
	}
}

// ReverseRotateA: velikost 1 -> no-op (bez logu)
func TestReverseRotateA_Size1_NoOp(t *testing.T) {
	ps := newState(3, 3)
	stack.Push(ps.A, 42) // A: [42]
	ReverseRotateA(ps)
	if got := vals(ps.A); len(got) != 1 || got[0] != 42 {
		t.Fatalf("expected A=[42], got %v", got)
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %v", ps.OpList)
	}
}

// ReverseRotateA: �sp\u011bch \u2013 posledn� prvek jde na vr\u0161ek, zaloguje RRA
func TestReverseRotateA_Success_OrderAndLog(t *testing.T) {
	ps := newState(5, 5)
	// postav [3,2,1] (top=3, second=2, bottom=1)
	stack.Push(ps.A, 1)
	stack.Push(ps.A, 2)
	stack.Push(ps.A, 3)

	ReverseRotateA(ps)

	// o\u010dek�v�me [1,3,2]
	want := []int{1, 3, 2}
	got := vals(ps.A)
	if len(got) != len(want) || got[0] != want[0] || got[1] != want[1] || got[2] != want[2] {
		t.Fatalf("after rra A=%v; want %v", got, want)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RRA {
		t.Fatalf("expected log [RRA], got %v", ps.OpList)
	}
}

// ReverseRotateB: �sp\u011bch \u2013 analogicky k A, zaloguje RRB
func TestReverseRotateB_Success_OrderAndLog(t *testing.T) {
	ps := newState(5, 5)
	stack.Push(ps.B, 10)
	stack.Push(ps.B, 20)
	stack.Push(ps.B, 30) // B: [30,20,10]

	ReverseRotateB(ps)

	want := []int{10, 30, 20}
	got := vals(ps.B)
	if len(got) != len(want) || got[0] != want[0] || got[1] != want[1] || got[2] != want[2] {
		t.Fatalf("after rrb B=%v; want %v", got, want)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RRB {
		t.Fatalf("expected log [RRB], got %v", ps.OpList)
	}
}

// ReverseRotateAB: ob\u011b rotace usp\u011bj� -> loguje se RRR (ne RRA/RRB)
func TestReverseRotateAB_Both_Success_LogRRR(t *testing.T) {
	ps := newState(5, 5)
	// A: [3,2,1]
	stack.Push(ps.A, 1); stack.Push(ps.A, 2); stack.Push(ps.A, 3)
	// B: [6,5,4]
	stack.Push(ps.B, 4); stack.Push(ps.B, 5); stack.Push(ps.B, 6)

	ReverseRotateAB(ps)

	// A -> [1,3,2]; B -> [4,6,5]
	wantA := []int{1, 3, 2}
	wantB := []int{4, 6, 5}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 3 || gotA[0] != wantA[0] || gotA[1] != wantA[1] || gotA[2] != wantA[2] {
		t.Fatalf("after rrr A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 3 || gotB[0] != wantB[0] || gotB[1] != wantB[1] || gotB[2] != wantB[2] {
		t.Fatalf("after rrr B=%v; want %v", gotB, wantB)
	}

	if len(ps.OpList) != 1 || ps.OpList[0] != RRR {
		t.Fatalf("expected log [RRR], got %v", ps.OpList)
	}
}

// ReverseRotateAB: usp\u011bje jen A -> loguje se RRA
func TestReverseRotateAB_OnlyA_Success_LogRRA(t *testing.T) {
	ps := newState(5, 5)
	// A: [2,1]
	stack.Push(ps.A, 1); stack.Push(ps.A, 2)
	// B: size<=1  (no-op)
	stack.Push(ps.B, 9)

	ReverseRotateAB(ps)

	// A -> [1,2]; B beze zm\u011bny [9]
	wantA := []int{1, 2}
	wantB := []int{9}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 2 || gotA[0] != wantA[0] || gotA[1] != wantA[1] {
		t.Fatalf("after rrr (only A) A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 1 || gotB[0] != wantB[0] {
		t.Fatalf("after rrr (only A) B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RRA {
		t.Fatalf("expected log [RRA], got %v", ps.OpList)
	}
}

// ReverseRotateAB: usp\u011bje jen B -> loguje se RRB
func TestReverseRotateAB_OnlyB_Success_LogRRB(t *testing.T) {
	ps := newState(5, 5)
	// A: size<=1 (no-op)
	stack.Push(ps.A, 7)
	// B: [2,1]
	stack.Push(ps.B, 1); stack.Push(ps.B, 2)

	ReverseRotateAB(ps)

	// A beze zm\u011bny [7], B -> [1,2]
	wantA := []int{7}
	wantB := []int{1, 2}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 1 || gotA[0] != wantA[0] {
		t.Fatalf("after rrr (only B) A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 2 || gotB[0] != wantB[0] || gotB[1] != wantB[1] {
		t.Fatalf("after rrr (only B) B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RRB {
		t.Fatalf("expected log [RRB], got %v", ps.OpList)
	}
}
