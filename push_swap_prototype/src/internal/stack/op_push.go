package stack


func push(src *Stack, dest *Stack) {
	if IsFull(dest) {
		return
	}
	dest_i := NextUp(dest, dest.Top)
	dest.Stack[dest_i] = src.Stack[src.Top]
	dest.Top = dest_i
	src.Stack[src.Top] = 0
	src.Top = NextDown(src, src.Top)
}

func PushA(ps *PushSwapData) {
	push(ps.B, ps.A)
	if ps.WritingMode {
		SaveOp(ps, PA)
	}
}

func PushB(ps *PushSwapData) {
	push(ps.A, ps.B)
	if ps.WritingMode {
		SaveOp(ps, PB)
	}
}