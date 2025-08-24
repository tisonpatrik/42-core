package solver

import (
	"push_swap_prototype/internal/stack"
)

// sortThree sorts three elements in a chunk
func sortThree(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stk := locToStack(ps, chunk.Loc)
	max := ChunkMaxValue(ps, chunk)
	switch chunk.Loc {
	case stack.TOP_A:
		sortThreeTopA(ps, chunk, stk, max)
	case stack.BOTTOM_A:
		sortThreeBottomA(ps, chunk, stk, max)
	case stack.TOP_B:
		sortThreeTopB(ps, chunk, stk, max)
	case stack.BOTTOM_B:
		sortThreeBottomB(ps, chunk, stk, max)
	}
}

// sortThreeTopA sorts three elements when chunk is at TOP_A
func sortThreeTopA(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
	
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

func sortThreeTopB(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
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

func sortThreeBottomA(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
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

// sortThreeBottomB sorts three elements when chunk is at BOTTOM_B
func sortThreeBottomB(ps *stack.PushSwapData, chunk *stack.Chunk, stk *stack.Stack, max int) {
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


