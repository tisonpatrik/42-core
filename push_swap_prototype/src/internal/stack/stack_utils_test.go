package stack

import "testing"


func mustPanic(t *testing.T, fn func(), msg string) {
	t.Helper()
	defer func() {
		if r := recover(); r == nil {
			t.Fatalf("expected panic: %s", msg)
		}
	}()
	fn()
}

func snapshotValues(s *Stack) []int {
	n := GetSize(s)
	out := make([]int, n)
	for i := range n {
		out[i] = GetValue(s, i)
	}
	return out
}


func TestInitEmpty(t *testing.T) {
	s := InitStack(3)
	if GetSize(s) != 0 || s.top != -1 || s.bottom != -1 {
		t.Fatalf("expected empty (-1/-1), got size=%d top=%d bottom=%d", GetSize(s), s.top, s.bottom)
	}
	// out-of-bounds GetValue -> null
	if v := GetValue(s, 0); v != NullValue() {
		t.Fatalf("expected nullValue on empty GetValue, got %d", v)
	}
}

func TestPushAndPeekBasic(t *testing.T) {
	s := InitStack(3)
	Push(s, 1)
	if GetSize(s) != 1 || s.top != 0 || s.bottom != 0 {
		t.Fatalf("after 1 push expected size=1 top=0 bottom=0, got size=%d top=%d bottom=%d", GetSize(s), s.top, s.bottom)
	}
	if p := Peek(s); p == nil || *p != 1 {
		t.Fatalf("peek expected 1, got %v", p)
	}

	// další push by měl wrapnout top dozadu
	Push(s, 2) // logicky [2,1]
	Push(s, 3) // logicky [3,2,1]
	want := []int{3, 2, 1}
	got := snapshotValues(s)
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("values %v; want %v", got, want)
		}
	}
	// plný stack musí panikovat
	mustPanic(t, func() { Push(s, 4) }, "push into full stack")
}

func TestPushRejectsNegative(t *testing.T) {
    s := InitStack(2)
    // -5 (a obecn\u011b < 0) nejsou povoleny
    mustPanic(t, func() { Push(s, -5) }, "negative not allowed")

    // 0 je povoleno
    Push(s, 0)
    if GetSize(s) != 1 || *Peek(s) != 0 {
        t.Fatalf("expected stack with 0 pushed on top, got size=%d top=%v",
            GetSize(s), Peek(s))
    }
}

func TestPopBasicAndToEmpty(t *testing.T) {
	s := InitStack(3)
	Push(s, 1)
	Push(s, 2)
	Push(s, 3) // [3,2,1]

	if v := Pop(s); v != 3 {
		t.Fatalf("pop expected 3, got %d", v)
	}
	if v := Pop(s); v != 2 {
		t.Fatalf("pop expected 2, got %d", v)
	}
	if v := Pop(s); v != 1 {
		t.Fatalf("pop expected 1, got %d", v)
	}
	// teď prázdný
	if GetSize(s) != 0 || s.top != -1 || s.bottom != -1 {
		t.Fatalf("after popping last element expected empty, got size=%d top=%d bottom=%d", GetSize(s), s.top, s.bottom)
	}
	// pop z prázdného vrací null
	if v := Pop(s); v != NullValue() {
		t.Fatalf("pop from empty expected nullValue, got %d", v)
	}
}

func TestRotate(t *testing.T) {
	s := InitStack(4)
	// naplníme 3 prvky -> [3,2,1]
	Push(s, 1); Push(s, 2); Push(s, 3)

	if !Rotate(s) {
		t.Fatalf("rotate should succeed on size>1")
	}
	// po rotate: [2,1,3]
	want := []int{2, 1, 3}
	got := snapshotValues(s)
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("after rotate values %v; want %v", got, want)
		}
	}

	// size 0/1 -> no-op
	s2 := InitStack(3)
	if Rotate(s2) {
		t.Fatalf("rotate on empty should be false")
	}
	Push(s2, 10)
	if Rotate(s2) {
		t.Fatalf("rotate on size=1 should be false")
	}
}

func TestReverseRotate(t *testing.T) {
	s := InitStack(4)
	// [3,2,1]
	Push(s, 1); Push(s, 2); Push(s, 3)

	if !ReverseRotate(s) {
		t.Fatalf("reverse rotate should succeed on size>1")
	}
	// po reverse rotate: [1,3,2]
	want := []int{1, 3, 2}
	got := snapshotValues(s)
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("after reverse rotate values %v; want %v", got, want)
		}
	}

	// size 0/1 -> no-op
	s2 := InitStack(3)
	if ReverseRotate(s2) {
		t.Fatalf("reverse rotate on empty should be false")
	}
	Push(s2, 10)
	if ReverseRotate(s2) {
		t.Fatalf("reverse rotate on size=1 should be false")
	}
}

func TestSwap(t *testing.T) {
	s := InitStack(5)
	Push(s, 1); Push(s, 2); Push(s, 3) // [3,2,1]
	if !Swap(s) {
		t.Fatalf("swap should succeed")
	}
	// po swap: [2,3,1]
	want := []int{2, 3, 1}
	got := snapshotValues(s)
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("after swap values %v; want %v", got, want)
		}
	}

	// swap na 0/1 prvku -> false
	s2 := InitStack(2)
	if Swap(s2) {
		t.Fatalf("swap on empty should be false")
	}
	Push(s2, 42)
	if Swap(s2) {
		t.Fatalf("swap on size=1 should be false")
	}
}

func TestFillStack(t *testing.T) {
    s := InitStack(3)
    FillStack(s, []int{1, 2, 3}) // v�sledn\u011b [3,2,1]
    want := []int{3, 2, 1}
    got := snapshotValues(s)
    for i := range want {
        if got[i] != want[i] {
            t.Fatalf("after FillStack values %v; want %v", got, want)
        }
    }
    // \u0161patn� d�lka po\u0159�d panika
    mustPanic(t, func() { FillStack(s, []int{1, 2}) }, "len(values) must equal capacity")

    // 0 je povoleno
    s2 := InitStack(1)
    FillStack(s2, []int{0})
    if v := GetValue(s2, 0); v != 0 {
        t.Fatalf("expected FillStack with 0 to succeed, got %d", v)
    }

    // negativn� je po\u0159�d zak�z�no
    mustPanic(t, func() { FillStack(InitStack(1), []int{-5}) }, "negative not allowed")
}

func TestIsFullAndGetValueBounds(t *testing.T) {
	s := InitStack(2)
	if IsFull(s) {
		t.Fatalf("empty should not be full")
	}
	Push(s, 1); Push(s, 2)
	if !IsFull(s) {
		t.Fatalf("should be full after 2 pushes")
	}
	// GetValue bounds
	if v := GetValue(s, -1); v != NullValue() {
		t.Fatalf("GetValue(-1) should return nullValue")
	}
	if v := GetValue(s, 2); v != NullValue() {
		t.Fatalf("GetValue(out of size) should return nullValue")
	}
}

func TestIsSorted(t *testing.T) {
	// sorted: [1,2,3] (logically from top)
	s := InitStack(3)
	Push(s, 1); Push(s, 2); Push(s, 3) // [3,2,1] -> this is not "1..n" from top
	if IsSorted(s) {
		t.Fatalf("expected not sorted for [3,2,1] in this definition")
	}
	// make [1,2,3] logically: reverse rotate twice from [3,2,1] -> [1,3,2], then rotate -> [3,2,1]… easier: fill manually
	s2 := InitStack(3)
	// we want GetValue(0..2) = [1,2,3]
	// we achieve this by pushing 3,2,1
	Push(s2, 3); Push(s2, 2); Push(s2, 1) // [1,2,3]
	if !IsSorted(s2) {
		t.Fatalf("expected sorted for [1,2,3]")
	}
}

