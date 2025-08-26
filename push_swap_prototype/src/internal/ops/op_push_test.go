package ops

import (
	"testing"

	"push_swap_prototype/internal/stack"
)

// --- helpers ---

func newState(capA, capB int) *SortingState {
	return &SortingState{
		A:      stack.InitStack(capA),
		B:      stack.InitStack(capB),
		OpList: nil, // SaveOp by měl appendovat
	}
}

func vals(s *stack.Stack) []int {
	n := stack.GetSize(s)
	out := make([]int, n)
	for i := 0; i < n; i++ {
		out[i] = stack.GetValue(s, i) // 0 = top, 1 = druhý...
	}
	return out
}

// --- tests ---

// No-op: B prázdný, A ne/ano prázdný -> nic se nestane, žádný záznam v logu.
func TestPushA_EmptySource_NoOp(t *testing.T) {
	ps := newState(3, 3) // A prázdná, B prázdná

	// sanity
	if stack.GetSize(ps.B) != 0 {
		t.Fatalf("arrange failed: expected B empty")
	}

	PushA(ps)

	if stack.GetSize(ps.A) != 0 || stack.GetSize(ps.B) != 0 {
		t.Fatalf("expected sizes A=0,B=0; got A=%d,B=%d", stack.GetSize(ps.A), stack.GetSize(ps.B))
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %d", len(ps.OpList))
	}
}

// No-op: cíl plný → PushA nic neprovede, nic neloguje.
func TestPushA_DestFull_NoOp(t *testing.T) {
	ps := newState(2, 3)
	// naplň A (cíl) na kapacitu
	stack.Push(ps.A, 10)
	stack.Push(ps.A, 20)
	if !stack.IsFull(ps.A) {
		t.Fatalf("arrange failed: A should be full")
	}
	// B má něco k přesunutí
	stack.Push(ps.B, 100)

	PushA(ps)

	// velikosti beze změny
	if !stack.IsFull(ps.A) || stack.GetSize(ps.B) != 1 {
		t.Fatalf("expected A full and B size=1; got A full=%v, B size=%d", stack.IsFull(ps.A), stack.GetSize(ps.B))
	}
	if len(ps.OpList) != 0 {
		t.Fatalf("expected no ops logged, got %d", len(ps.OpList))
	}
}

// Základní přesun: B -> A, velikosti i hodnoty odpovídají.
func TestPushA_SingleMove(t *testing.T) {
	ps := newState(3, 3)
	stack.Push(ps.B, 100) // B: [100]

	ok := push(ps.B, ps.A)
	if !ok {
		t.Fatalf("push should succeed")
	}

	if stack.GetSize(ps.A) != 1 || stack.GetSize(ps.B) != 0 {
		t.Fatalf("expected sizes A=1,B=0; got A=%d,B=%d", stack.GetSize(ps.A), stack.GetSize(ps.B))
	}
	v := vals(ps.A)
	if len(v) != 1 || v[0] != 100 {
		t.Fatalf("expected A=[100], got %v", v)
	}
}

// Veřejná API + log: PushA zaloguje PA jen při úspěchu.
func TestPushA_LogsOnSuccessOnly(t *testing.T) {
	ps := newState(3, 3)

	// 1) zdroj prázdný → no-op, bez logu
	PushA(ps)
	if len(ps.OpList) != 0 {
		t.Fatalf("expected 0 ops, got %d", len(ps.OpList))
	}

	// 2) něco do B a proveď PushA → zaloguje 1× PA
	stack.Push(ps.B, 7)
	PushA(ps)
	if len(ps.OpList) != 1 || ps.OpList[0] != PA {
		t.Fatalf("expected log [PA], got %v", ps.OpList)
	}
}

// Dva po sobě jdoucí přesuny B -> A zachovají LIFO pořadí na A.
func TestPushA_Twice_LIFO_Order(t *testing.T) {
	ps := newState(5, 5)
	// B: pushni b1, pak b2 => TOP je b2
	b1, b2 := 50, 200
	stack.Push(ps.B, b1)
	stack.Push(ps.B, b2)

	PushA(ps) // A: [b2], B: [b1]
	PushA(ps) // A: [b1, b2], B: []

	if aSize, bSize := stack.GetSize(ps.A), stack.GetSize(ps.B); aSize != 2 || bSize != 0 {
		t.Fatalf("expected sizes A=2,B=0; got A=%d,B=%d", aSize, bSize)
	}
	a := vals(ps.A)
	want := []int{b1, b2} // top=b1, second=b2 (LIFO)
	if len(a) != 2 || a[0] != want[0] || a[1] != want[1] {
		t.Fatalf("expected A=%v, got %v", want, a)
	}
	// log: přesně 2× PA
	if len(ps.OpList) != 2 || ps.OpList[0] != PA || ps.OpList[1] != PA {
		t.Fatalf("expected log [PA,PA], got %v", ps.OpList)
	}
}

// Symetrie: PushB funguje z A do B stejně.
func TestPushB_MirrorOfPushA(t *testing.T) {
	ps := newState(4, 4)
	// A: [1,2] (top=2)
	stack.Push(ps.A, 1)
	stack.Push(ps.A, 2)

	PushB(ps) // B: [2], A: [1]
	PushB(ps) // B: [1,2], A: []

	if aSize, bSize := stack.GetSize(ps.A), stack.GetSize(ps.B); aSize != 0 || bSize != 2 {
		t.Fatalf("expected sizes A=0,B=2; got A=%d,B=%d", aSize, bSize)
	}
	b := vals(ps.B)
	want := []int{1, 2} // top=1, second=2 (LIFO z A)
	if len(b) != 2 || b[0] != want[0] || b[1] != want[1] {
		t.Fatalf("expected B=%v, got %v", want, b)
	}
	// log: [PB, PB]
	if len(ps.OpList) != 2 || ps.OpList[0] != PB || ps.OpList[1] != PB {
		t.Fatalf("expected log [PB,PB], got %v", ps.OpList)
	}
}
