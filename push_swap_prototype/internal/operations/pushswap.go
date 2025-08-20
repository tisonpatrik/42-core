package operations

import "push_swap_prototype/internal/stack"

// PushSwapStacks represents the two stacks used in push swap
type PushSwapStacks struct {
	A *stack.Stack
	B *stack.Stack
}

// NewPushSwapStacks creates new push swap stacks
func NewPushSwapStacks() *PushSwapStacks {
	return &PushSwapStacks{
		A: stack.New(),
		B: stack.New(),
	}
}

// InitializeFromSlice initializes stack A with values from a slice
func (ps *PushSwapStacks) InitializeFromSlice(values []int) {
	ps.A = stack.FromSlice(values)
}

// SA swaps the first 2 elements at the top of stack A
func (ps *PushSwapStacks) SA() bool {
	return ps.A.SwapTop()
}



// PA pushes the first element of B to A
func (ps *PushSwapStacks) PA() bool {
	return ps.A.PushFrom(ps.B)
}

// PB pushes the first element of A to B
func (ps *PushSwapStacks) PB() bool {
	return ps.B.PushFrom(ps.A)
}

// RA rotates stack A up (first element becomes last)
func (ps *PushSwapStacks) RA() bool {
	return ps.A.RotateUp()
}

// RB rotates stack B up (first element becomes last)
func (ps *PushSwapStacks) RB() bool {
	return ps.B.RotateUp()
}

// RR rotates both stacks up
func (ps *PushSwapStacks) RR() bool {
	aOk := ps.A.RotateUp()
	bOk := ps.B.RotateUp()
	return aOk || bOk
}

// RRA rotates stack A down (last element becomes first)
func (ps *PushSwapStacks) RRA() bool {
	return ps.A.RotateDown()
}

// RRB rotates stack B down (last element becomes first)
func (ps *PushSwapStacks) RRB() bool {
	return ps.B.RotateDown()
}

// RRR rotates both stacks down
func (ps *PushSwapStacks) RRR() bool {
	aOk := ps.A.RotateDown()
	bOk := ps.B.RotateDown()
	return aOk || bOk
}




