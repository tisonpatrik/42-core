package ops

import (
	"testing"

	"push_swap_prototype/internal/stack"
)

// RotateA: prázdný -> no-op (bez logu)
func TestRotateA_Empty_NoOp(t *testing.T) {
	ps := newState(3, 3)
	RotateA(ps)
	if got := stack.GetSize(ps.A); got != 0 {
		t.Fatalf("expected A size 0, got %d", got)
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %v", ps.OpList)
	}
}

// RotateA: velikost 1 -> no-op (bez logu)
func TestRotateA_Size1_NoOp(t *testing.T) {
	ps := newState(3, 3)
	stack.Push(ps.A, 42) // A: [42]
	RotateA(ps)
	if got := vals(ps.A); len(got) != 1 || got[0] != 42 {
		t.Fatalf("expected A=[42], got %v", got)
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %v", ps.OpList)
	}
}

// RotateA: úspěch – první jde na konec, loguje RA
func TestRotateA_Success_OrderAndLog(t *testing.T) {
	ps := newState(5, 5)
	// A: [3,2,1] (top=3, second=2, bottom=1)
	stack.Push(ps.A, 1)
	stack.Push(ps.A, 2)
	stack.Push(ps.A, 3)

	RotateA(ps)

	// očekáváme [2,1,3]
	want := []int{2, 1, 3}
	got := vals(ps.A)
	if len(got) != len(want) || got[0] != want[0] || got[1] != want[1] || got[2] != want[2] {
		t.Fatalf("after ra A=%v; want %v", got, want)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RA {
		t.Fatalf("expected log [RA], got %v", ps.OpList)
	}
}

// RotateB: úspěch – analogicky k A, loguje RB
func TestRotateB_Success_OrderAndLog(t *testing.T) {
	ps := newState(5, 5)
	// B: [30,20,10]
	stack.Push(ps.B, 10)
	stack.Push(ps.B, 20)
	stack.Push(ps.B, 30)

	RotateB(ps)

	// očekáváme [20,10,30]
	want := []int{20, 10, 30}
	got := vals(ps.B)
	if len(got) != len(want) || got[0] != want[0] || got[1] != want[1] || got[2] != want[2] {
		t.Fatalf("after rb B=%v; want %v", got, want)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RB {
		t.Fatalf("expected log [RB], got %v", ps.OpList)
	}
}

// RotateAB: obě rotace uspějí -> loguje se RR (ne RA/RB)
func TestRotateAB_Both_Success_LogRR(t *testing.T) {
	ps := newState(5, 5)
	// A: [3,2,1], B: [6,5,4]
	stack.Push(ps.A, 1); stack.Push(ps.A, 2); stack.Push(ps.A, 3)
	stack.Push(ps.B, 4); stack.Push(ps.B, 5); stack.Push(ps.B, 6)

	RotateAB(ps)

	// A -> [2,1,3]; B -> [5,4,6]
	wantA := []int{2, 1, 3}
	wantB := []int{5, 4, 6}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 3 || gotA[0] != wantA[0] || gotA[1] != wantA[1] || gotA[2] != wantA[2] {
		t.Fatalf("after rr A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 3 || gotB[0] != wantB[0] || gotB[1] != wantB[1] || gotB[2] != wantB[2] {
		t.Fatalf("after rr B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RR {
		t.Fatalf("expected log [RR], got %v", ps.OpList)
	}
}

// RotateAB: uspěje jen A -> loguje se RA
func TestRotateAB_OnlyA_Success_LogRA(t *testing.T) {
	ps := newState(5, 5)
	// A: [2,1] -> rotace jde
	stack.Push(ps.A, 1); stack.Push(ps.A, 2)
	// B: size<=1 -> no-op
	stack.Push(ps.B, 9)

	RotateAB(ps)

	// A -> [1,2]; B beze změny [9]
	wantA := []int{1, 2}
	wantB := []int{9}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 2 || gotA[0] != wantA[0] || gotA[1] != wantA[1] {
		t.Fatalf("after rr (only A) A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 1 || gotB[0] != wantB[0] {
		t.Fatalf("after rr (only A) B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RA {
		t.Fatalf("expected log [RA], got %v", ps.OpList)
	}
}

// RotateAB: uspěje jen B -> loguje se RB
func TestRotateAB_OnlyB_Success_LogRB(t *testing.T) {
	ps := newState(5, 5)
	// A: size<=1 -> no-op
	stack.Push(ps.A, 7)
	// B: [2,1] -> rotace jde
	stack.Push(ps.B, 1); stack.Push(ps.B, 2)

	RotateAB(ps)

	// A beze změny [7], B -> [1,2]
	wantA := []int{7}
	wantB := []int{1, 2}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 1 || gotA[0] != wantA[0] {
		t.Fatalf("after rr (only B) A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 2 || gotB[0] != wantB[0] || gotB[1] != wantB[1] {
		t.Fatalf("after rr (only B) B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != RB {
		t.Fatalf("expected log [RB], got %v", ps.OpList)
	}
}
