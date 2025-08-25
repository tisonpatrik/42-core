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

func SortThreeTopA(ps *stack.PushSwapData, to_sort *stack.Chunk, stk *stack.Stack, max int) {
	if stack.Value(stk, stk.Top) == max {
		stack.SwapA(ps)
		stack.RotateA(ps)
		stack.SwapA(ps)
		stack.ReverseRotateA(ps)
	} else if stack.Value(stk, stack.NextDown(stk, stk.Top)) == max {
		stack.RotateA(ps)
		stack.SwapA(ps)
		stack.ReverseRotateA(ps)
	}

	to_sort.Loc = stack.TOP_A
	to_sort.Size -= 1
	
	SortTwo(ps, to_sort)
}

func SortThreeTopB(ps *stack.PushSwapData, to_sort *stack.Chunk, stk *stack.Stack, max int) {
	stack.PushA(ps)

	if stack.Value(stk, stk.Top) == max {
		stack.PushA(ps)
		stack.SwapA(ps)
	} else if stack.Value(stk, stack.NextDown(stk, stk.Top)) == max {
		stack.SwapB(ps)
		stack.PushA(ps)
		stack.SwapA(ps)
	} else {
		stack.PushA(ps)
	}
	stack.PushA(ps)

	to_sort.Loc = stack.TOP_A
	to_sort.Size -= 1

	SortTwo(ps, to_sort)
}

func SortThreeBottomA(ps *stack.PushSwapData, to_sort *stack.Chunk, stk *stack.Stack, max int) {
	stack.ReverseRotateA(ps)
	stack.ReverseRotateA(ps)

	if stack.Value(stk, stk.Top) == max {
		stack.SwapA(ps)
		stack.ReverseRotateA(ps)
	} else if stack.Value(stk, stack.NextDown(stk, stk.Top)) == max {
		stack.ReverseRotateA(ps)
	}else {
		stack.PushB(ps)
		stack.ReverseRotateA(ps)
		stack.SwapA(ps)
		stack.PushA(ps)
	}

	to_sort.Loc = stack.TOP_A
	to_sort.Size -= 1
	SortTwo(ps, to_sort)
}

func SortThreeBottomB(ps *stack.PushSwapData, to_sort *stack.Chunk, stk *stack.Stack, max int) {
	stack.ReverseRotateB(ps)
	stack.ReverseRotateB(ps)

	if stack.Value(stk, stk.Top) == max {
		stack.PushA(ps)
		stack.ReverseRotateB(ps)
	}else if stack.Value(stk, stack.NextDown(stk, stk.Top)) == max {
		stack.SwapB(ps)
		stack.PushA(ps)
		stack.ReverseRotateB(ps)
	}	else {
		stack.ReverseRotateB(ps)
		stack.PushA(ps)
	}

	to_sort.Loc = stack.TOP_B
	to_sort.Size -= 1
	SortTwo(ps, to_sort)
}