package solver

import (
	"push_swap_prototype/internal/stack"
)

// sortThree třídí tři prvky v chunku shodně s C implementací
func SortThree(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stk := locToStack(ps, chunk.Loc)
	max := ChunkMaxValue(ps, chunk)

	switch chunk.Loc {
	case stack.TOP_A:
		SortThreeTopA(ps, chunk, stk, max)
	case stack.BOTTOM_A:
		SortThreeBottomA(ps, chunk, stk, max)
	case stack.TOP_B:
		SortThreeTopB(ps, chunk, stk, max)
	case stack.BOTTOM_B:
		SortThreeBottomB(ps, chunk, stk, max)
	}
}

// sortThreeTopA třídí tři prvky, když je chunk na TOP_A
func SortThreeTopA(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
	if stk.Value(stk.GetTop()) == max {
		stack.Swap_a(ps)
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	} else if stk.Value(stk.NextDown(stk.GetTop())) == max {
		stack.Rotate_a(ps)
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	}

	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	SortTwo(ps, chunk)
}

// sortThreeTopB třídí tři prvky, když je chunk na TOP_B
func SortThreeTopB(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
	stack.Push_a(ps)
	if stk.Value(stk.GetTop()) == max {
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else if stk.Value(stk.NextDown(stk.GetTop())) == max {
		stack.Swap_b(ps)
		stack.Push_a(ps)
		stack.Swap_a(ps)
	} else {
		stack.Push_a(ps)
	}
	stack.Push_a(ps)

	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	SortTwo(ps, chunk)
}

// sortThreeBottomA třídí tři prvky, když je chunk na BOTTOM_A
func SortThreeBottomA(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	if stk.Value(stk.GetTop()) == max {
		stack.Swap_a(ps)
		stack.R_rotate_a(ps)
	} else if stk.Value(stk.NextDown(stk.GetTop())) == max {
		stack.R_rotate_a(ps)
	} else {
		stack.Push_b(ps)
		stack.R_rotate_a(ps)
		stack.Swap_a(ps)
		stack.Push_a(ps)
	}

	chunk.Loc = stack.TOP_A
	chunk.Size -= 1
	SortTwo(ps, chunk)
}

// sortThreeBottomB třídí tři prvky, když je chunk na BOTTOM_B
func SortThreeBottomB(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	if stk.Value(stk.GetTop()) == max {
		stack.Push_a(ps)
		stack.R_rotate_b(ps)
	} else if stk.Value(stk.NextDown(stk.GetTop())) == max {
		stack.Swap_b(ps)
		stack.Push_a(ps)
		stack.R_rotate_b(ps)
	} else {
		stack.R_rotate_b(ps)
		stack.Push_a(ps)
	}

	chunk.Loc = stack.TOP_B
	chunk.Size -= 1
	SortTwo(ps, chunk)
}