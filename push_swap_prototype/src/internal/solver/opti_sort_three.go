package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/stack"
)

// sortThree třídí tři prvky v chunku shodně s C implementací
func SortThree(ps *stack.SortingState, chunk_item *chunk.Chunk) {
	
	
	stk := locToStack(ps, chunk_item.Loc)
	max := ChunkMaxValue(ps, chunk_item)


	switch chunk_item.Loc {
	case chunk.TOP_A:
		SortThreeTopA(ps, chunk_item, stk, max)
	case chunk.BOTTOM_A:
		SortThreeBottomA(ps, chunk_item, stk, max)
	case chunk.TOP_B:
		SortThreeTopB(ps, chunk_item, stk, max)
	case chunk.BOTTOM_B:
		SortThreeBottomB(ps, chunk_item, stk, max)
	}
}

func SortThreeTopA(ps *stack.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
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

	to_sort.Loc = chunk.TOP_A
	to_sort.Size -= 1
	
	SortTwo(ps, to_sort)
}

func SortThreeTopB(ps *stack.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
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

	to_sort.Loc = chunk.TOP_A
	to_sort.Size -= 1

	SortTwo(ps, to_sort)
}

func SortThreeBottomA(ps *stack.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
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

	to_sort.Loc = chunk.TOP_A
	to_sort.Size -= 1
	SortTwo(ps, to_sort)
}

func SortThreeBottomB(ps *stack.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
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

	to_sort.Loc = chunk.TOP_B
	to_sort.Size -= 1
	SortTwo(ps, to_sort)
}