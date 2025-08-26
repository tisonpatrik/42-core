package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

func EasySort(ps *ops.SortingState, to_sort *chunk.Chunk) {
	
	for ; to_sort.Loc != chunk.TOP_A && to_sort.Size > 0; {
		
		if stack.GetValue(ps.A, 1) == ChunkValue(ps, to_sort, 1) + 1 && to_sort.Size > 0 {
			SortOne(ps, to_sort)
		}else if stack.GetValue(ps.A, 1) == ChunkValue(ps, to_sort, 2) + 1 && to_sort.Size > 1 {
			EasySortSecond(ps, to_sort)
		}else {
			break
		}
	}
	
}

func EasySortSecond(ps *ops.SortingState, to_sort *chunk.Chunk) {
	switch to_sort.Loc {
	case chunk.TOP_B:
		HandleTopB(ps, to_sort)
	case chunk.BOTTOM_A:
		HandleBottomA(ps, to_sort)
	case chunk.BOTTOM_B:
		HandleBottomB(ps, to_sort)
	}
	to_sort.Size--
}

func HandleTopB(ps *ops.SortingState, to_sort *chunk.Chunk) {
	ops.SwapB(ps)
	ops.PushA(ps)
	if stack.GetValue(ps.B, 1) == stack.GetValue(ps.A, 1) - 1 {
		ops.PushA(ps)
		to_sort.Size--
	}
}

func HandleBottomA(ps *ops.SortingState, to_sort *chunk.Chunk) {
	ops.ReverseRotateA(ps)
	ops.ReverseRotateA(ps)
	ops.SwapA(ps)
	if stack.GetValue(ps.A, 1) == stack.GetValue(ps.A, 2) - 1 {
		to_sort.Size--
	} else {
		ops.RotateA(ps)
	}
}

func HandleBottomB(ps *ops.SortingState, to_sort *chunk.Chunk) {
	ops.ReverseRotateB(ps)
	ops.ReverseRotateB(ps)

	ops.PushA(ps)  // FIXED: Match C implementation - push_a first, then swap_b
	if stack.GetValue(ps.B, 1) == stack.GetValue(ps.A, 1) - 1 {
		ops.PushA(ps)
		to_sort.Size--
	} else {
		ops.RotateB(ps)
	}
}