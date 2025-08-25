package solver

import (
	"push_swap_prototype/internal/stack"
)

func EasySort(ps *stack.PushSwapData, to_sort *stack.Chunk) {
	
	for ; to_sort.Loc != stack.TOP_A && to_sort.Size > 0; {
		
		if stack.Value(ps.A, 1) == ChunkValue(ps, to_sort, 1) + 1 && to_sort.Size > 0 {
			SortOne(ps, to_sort)
		}else if stack.Value(ps.A, 1) == ChunkValue(ps, to_sort, 2) + 1 && to_sort.Size > 1 {
			EasySortSecond(ps, to_sort)
		}else {
			break
		}
	}
	
}

func EasySortSecond(ps *stack.PushSwapData, to_sort *stack.Chunk) {
	switch to_sort.Loc {
	case stack.TOP_B:
		HandleTopB(ps, to_sort)
	case stack.BOTTOM_A:
		HandleBottomA(ps, to_sort)
	case stack.BOTTOM_B:
		HandleBottomB(ps, to_sort)
	}
	to_sort.Size--
}

func HandleTopB(ps *stack.PushSwapData, to_sort *stack.Chunk) {
	stack.SwapB(ps)
	stack.PushA(ps)
	if stack.Value(ps.B, 1) == stack.Value(ps.A, 1) - 1 {
		stack.PushA(ps)
		to_sort.Size--
	}
}

func HandleBottomA(ps *stack.PushSwapData, to_sort *stack.Chunk) {
	stack.ReverseRotateA(ps)
	stack.ReverseRotateA(ps)
	stack.SwapA(ps)
	if stack.Value(ps.A, 1) == stack.Value(ps.A, 2) - 1 {
		to_sort.Size--
	} else {
		stack.RotateA(ps)
	}
}

func HandleBottomB(ps *stack.PushSwapData, to_sort *stack.Chunk) {
	stack.ReverseRotateB(ps)
	stack.ReverseRotateB(ps)
	stack.SwapB(ps)
	if stack.Value(ps.B, 1) == stack.Value(ps.B, 2) - 1 {
		to_sort.Size--
	} else {
		stack.RotateB(ps)
	}
}