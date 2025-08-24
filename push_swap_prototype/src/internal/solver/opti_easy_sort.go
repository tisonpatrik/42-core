package solver

import (
	"push_swap_prototype/internal/stack"
)

func EasySort(ps *stack.PushSwapData, chunk *stack.Chunk) {
	for chunk.Loc != stack.TOP_A && chunk.Size != 0 {
		if ps.A.GetValueAtPosition(1) == ChunkValue(ps, chunk, 1)+1 && chunk.Size > 0 {
			SortOne(ps, chunk)
		} else if ps.A.GetValueAtPosition(1) == ChunkValue(ps, chunk, 2)+1 && chunk.Size > 1 {
			EasySortSecond(ps, chunk)
		} else {
			break
		}
	}
}

func EasySortSecond(ps *stack.PushSwapData, chunk *stack.Chunk) {
	switch chunk.Loc {
	case stack.TOP_B:
		HandleTopB(ps, chunk)
	case stack.BOTTOM_A:
		HandleBottomA(ps, chunk)
	case stack.BOTTOM_B:
		HandleBottomB(ps, chunk)
	}
	chunk.Size--
}

func HandleTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.Swap_b(ps)
	stack.Push_a(ps)

	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
		chunk.Size--
	}
}

func HandleBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	stack.Swap_a(ps)

	if ps.A.GetValueAtPosition(1) == ps.A.GetValueAtPosition(2)-1 {
		chunk.Size--
	} else {
		stack.Rotate_a(ps)
	}
}

func HandleBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	stack.Push_a(ps)

	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
		chunk.Size--
	} else {
		stack.Rotate_b(ps)
	}
}
