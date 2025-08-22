package stack

// swap swaps the first 2 elements at the top of a stack (exactly like C swap)
func swap(stk *Stack) {
	// C implementation checks if second element exists by checking if it's 0
	// stk->stack[next_down(stk, stk->top)] == 0
	if stk.CurrentSize() < 2 {
		return
	}
	
	// Get the second element position using NextDown like C implementation
	secondPos := stk.NextDown(stk.GetTop())
	
	// Check if second element exists (not 0) - exactly like C implementation
	if stk.GetStack()[secondPos] == 0 {
		return
	}
	
	// Swap the top two elements
	stk.SwapTop()
}

// Swap_a swaps the first 2 elements at the top of stack A (like C swap_a)
func Swap_a(data *PushSwapData) {
	swap(data.A)
	if data.WritingMode {
		saveOp(data, SA)
	}
}

// Swap_b swaps the first 2 elements at the top of stack B (like C swap_b)
func Swap_b(data *PushSwapData) {
	swap(data.B)
	if data.WritingMode {
		saveOp(data, SB)
	}
}

// Swap_ab swaps the first 2 elements at the top of both stacks (like C swap_ab)
func Swap_ab(data *PushSwapData) {
	swap(data.A)
	swap(data.B)
	if data.WritingMode {
		saveOp(data, SS)
	}
}
