package stack

// push pushes an element from src to dest (like C push)
func push(src *Stack, dest *Stack) {
	dest.PushFrom(src)
}

// Push_a pushes the first element of B to A (like C push_a)
func Push_a(data *PushSwapData) {
	push(data.B, data.A)
	if data.WritingMode {
		saveOp(data, PA)
	}
}

// Push_b pushes the first element of A to B (like C push_b)
func Push_b(data *PushSwapData) {
	push(data.A, data.B)
	if data.WritingMode {
		saveOp(data, PB)
	}
}
