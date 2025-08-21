package operations

import (
	"push_swap_prototype/internal/stack"
)

// r_rotate rotates a stack down (last element becomes first) (like C r_rotate)
func r_rotate(stk *stack.Stack) {
	stk.RotateDown()
}

// R_rotate_a rotates stack A down (last element becomes first) (like C r_rotate_a)
func R_rotate_a(data *PushSwapData) {
	r_rotate(data.A)
	if data.WritingMode {
		saveOp(data, RRA)
	}
}

// R_rotate_b rotates stack B down (last element becomes first) (like C r_rotate_b)
func R_rotate_b(data *PushSwapData) {
	r_rotate(data.B)
	if data.WritingMode {
		saveOp(data, RRB)
	}
}

// R_rotate_ab rotates both stacks down (like C r_rotate_ab)
func R_rotate_ab(data *PushSwapData) {
	r_rotate(data.A)
	r_rotate(data.B)
	if data.WritingMode {
		saveOp(data, RRR)
	}
}
