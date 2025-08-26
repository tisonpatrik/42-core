package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// sortThree třídí tři prvky v chunku shodně s C implementací
func SortThree(ps *ops.SortingState, chunk_item *chunk.Chunk) {
	
	
	stk := locToStack(ps, chunk.GetLoc(chunk_item))
	max := ChunkMaxValue(ps, chunk_item)


	switch chunk.GetLoc(chunk_item) {
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

func SortThreeTopA(ps *ops.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
	if stack.GetValue(stk, stack.GetTop(stk)) == max {
		ops.SwapA(ps)
		ops.RotateA(ps)
		ops.SwapA(ps)
		ops.ReverseRotateA(ps)
	} else if stack.GetValue(stk, stack.Next(stk, stack.GetTop(stk))) == max {
		ops.RotateA(ps)
		ops.SwapA(ps)
		ops.ReverseRotateA(ps)
	}

	chunk.SetLoc(to_sort, chunk.TOP_A)
	chunk.SetSize(to_sort, chunk.GetSize(to_sort)-1)
	
	SortTwo(ps, to_sort)
}

func SortThreeTopB(ps *ops.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
	ops.PushA(ps)

	if stack.GetValue(stk, stack.GetTop(stk)) == max {
		ops.PushA(ps)
		ops.SwapA(ps)
	} else if stack.GetValue(stk, stack.Next(stk, stack.GetTop(stk))) == max {
		ops.SwapB(ps)
		ops.PushA(ps)
		ops.SwapA(ps)
	} else {
		ops.PushA(ps)
	}
	ops.PushA(ps)

	chunk.SetLoc(to_sort, chunk.TOP_A)
	chunk.SetSize(to_sort, chunk.GetSize(to_sort)-1)

	SortTwo(ps, to_sort)
}

func SortThreeBottomA(ps *ops.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
	ops.ReverseRotateA(ps)
	ops.ReverseRotateA(ps)

	if stack.GetValue(stk, stack.GetTop(stk)) == max {
		ops.SwapA(ps)
		ops.ReverseRotateA(ps)
	} else if stack.GetValue(stk, stack.Next(stk, stack.GetTop(stk))) == max {
		ops.ReverseRotateA(ps)
	}else {
		ops.PushB(ps)
		ops.ReverseRotateA(ps)
		ops.SwapA(ps)
		ops.PushA(ps)
	}

	chunk.SetLoc(to_sort, chunk.TOP_A)
	chunk.SetSize(to_sort, chunk.GetSize(to_sort)-1)
	SortTwo(ps, to_sort)
}

func SortThreeBottomB(ps *ops.SortingState, to_sort *chunk.Chunk, stk *stack.Stack, max int) {
	ops.ReverseRotateB(ps)
	ops.ReverseRotateB(ps)

	if stack.GetValue(stk, stack.GetTop(stk)) == max {
		ops.PushA(ps)
		ops.ReverseRotateB(ps)
	}else if stack.GetValue(stk, stack.Next(stk, stack.GetTop(stk))) == max {
		ops.SwapB(ps)
		ops.PushA(ps)
		ops.ReverseRotateB(ps)
	}	else {
		ops.ReverseRotateB(ps)
		ops.PushA(ps)
	}

	chunk.SetLoc(to_sort, chunk.TOP_B)
	chunk.SetSize(to_sort, chunk.GetSize(to_sort)-1)
	SortTwo(ps, to_sort)
}