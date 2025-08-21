package operations

import (
	"push_swap_prototype/internal/stack"
)

// rotate rotates a stack up (first element becomes last) (like C rotate)
func rotate(stk *stack.Stack) {
	stk.RotateUp()
}

// Rotate_a rotates stack A up (first element becomes last) (like C rotate_a)
func Rotate_a(data *PushSwapData) {
	rotate(data.A)
	if data.WritingMode {
		saveOp(data, RA)
	}
}

// Rotate_b rotates stack B up (first element becomes last) (like C rotate_b)
func Rotate_b(data *PushSwapData) {
	rotate(data.B)
	if data.WritingMode {
		saveOp(data, RB)
	}
}

// Rotate_ab rotates both stacks up (like C rotate_ab)
func Rotate_ab(data *PushSwapData) {
	rotate(data.A)
	rotate(data.B)
	if data.WritingMode {
		saveOp(data, RR)
	}
} 