package ops

import (
	"testing"

	"push_swap_prototype/internal/stack"
)

// SwapA: pr�zdn� -> no-op (bez logu)
func TestSwapA_Empty_NoOp(t *testing.T) {
	ps := newState(3, 3)
	SwapA(ps)
	if got := stack.GetSize(ps.A); got != 0 {
		t.Fatalf("expected A size 0, got %d", got)
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %v", ps.OpList)
	}
}

// SwapA: velikost 1 -> no-op (bez logu)
func TestSwapA_Size1_NoOp(t *testing.T) {
	ps := newState(3, 3)
	stack.Push(ps.A, 42) // A: [42]
	SwapA(ps)
	if got := vals(ps.A); len(got) != 1 || got[0] != 42 {
		t.Fatalf("expected A=[42], got %v", got)
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %v", ps.OpList)
	}
}

// SwapA: �sp\u011bch \u2013 proho\u010f vr\u0161ek a druh�, loguje SA
func TestSwapA_Success_OrderAndLog(t *testing.T) {
	ps := newState(5, 5)
	// A: [3,2,1] (top=3, second=2)
	stack.Push(ps.A, 1)
	stack.Push(ps.A, 2)
	stack.Push(ps.A, 3)

	SwapA(ps)

	// o\u010dek�v�me [2,3,1]
	want := []int{2, 3, 1}
	got := vals(ps.A)
	if len(got) != len(want) || got[0] != want[0] || got[1] != want[1] || got[2] != want[2] {
		t.Fatalf("after sa A=%v; want %v", got, want)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != SA {
		t.Fatalf("expected log [SA], got %v", ps.OpList)
	}
}

// SwapB: �sp\u011bch \u2013 analogicky k A, loguje SB
func TestSwapB_Success_OrderAndLog(t *testing.T) {
	ps := newState(5, 5)
	// B: [30,20,10]
	stack.Push(ps.B, 10)
	stack.Push(ps.B, 20)
	stack.Push(ps.B, 30)

	SwapB(ps)

	// o\u010dek�v�me [20,30,10]
	want := []int{20, 30, 10}
	got := vals(ps.B)
	if len(got) != len(want) || got[0] != want[0] || got[1] != want[1] || got[2] != want[2] {
		t.Fatalf("after sb B=%v; want %v", got, want)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != SB {
		t.Fatalf("expected log [SB], got %v", ps.OpList)
	}
}

// SwapAB: ob\u011b swapy usp\u011bj� -> loguje se SS (ne SA/SB)
func TestSwapAB_Both_Success_LogSS(t *testing.T) {
	ps := newState(5, 5)
	// A: [3,2,1], B: [6,5,4]
	stack.Push(ps.A, 1); stack.Push(ps.A, 2); stack.Push(ps.A, 3)
	stack.Push(ps.B, 4); stack.Push(ps.B, 5); stack.Push(ps.B, 6)

	SwapAB(ps)

	// A -> [2,3,1]; B -> [5,6,4]
	wantA := []int{2, 3, 1}
	wantB := []int{5, 6, 4}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 3 || gotA[0] != wantA[0] || gotA[1] != wantA[1] || gotA[2] != wantA[2] {
		t.Fatalf("after ss A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 3 || gotB[0] != wantB[0] || gotB[1] != wantB[1] || gotB[2] != wantB[2] {
		t.Fatalf("after ss B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != SS {
		t.Fatalf("expected log [SS], got %v", ps.OpList)
	}
}

// SwapAB: usp\u011bje jen A -> loguje se SA
func TestSwapAB_OnlyA_Success_LogSA(t *testing.T) {
	ps := newState(5, 5)
	// A: [2,1] -> swap jde
	stack.Push(ps.A, 1); stack.Push(ps.A, 2)
	// B: size<=1 -> no-op
	stack.Push(ps.B, 9)

	SwapAB(ps)

	// A -> [1,2]; B beze zm\u011bny [9]
	wantA := []int{1, 2}
	wantB := []int{9}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 2 || gotA[0] != wantA[0] || gotA[1] != wantA[1] {
		t.Fatalf("after ss (only A) A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 1 || gotB[0] != wantB[0] {
		t.Fatalf("after ss (only A) B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != SA {
		t.Fatalf("expected log [SA], got %v", ps.OpList)
	}
}

// SwapAB: usp\u011bje jen B -> loguje se SB
func TestSwapAB_OnlyB_Success_LogSB(t *testing.T) {
	ps := newState(5, 5)
	// A: size<=1 -> no-op
	stack.Push(ps.A, 7)
	// B: [2,1] -> swap jde
	stack.Push(ps.B, 1); stack.Push(ps.B, 2)

	SwapAB(ps)

	// A beze zm\u011bny [7], B -> [1,2]
	wantA := []int{7}
	wantB := []int{1, 2}
	gotA := vals(ps.A)
	gotB := vals(ps.B)
	if len(gotA) != 1 || gotA[0] != wantA[0] {
		t.Fatalf("after ss (only B) A=%v; want %v", gotA, wantA)
	}
	if len(gotB) != 2 || gotB[0] != wantB[0] || gotB[1] != wantB[1] {
		t.Fatalf("after ss (only B) B=%v; want %v", gotB, wantB)
	}
	if len(ps.OpList) != 1 || ps.OpList[0] != SB {
		t.Fatalf("expected log [SB], got %v", ps.OpList)
	}
}
