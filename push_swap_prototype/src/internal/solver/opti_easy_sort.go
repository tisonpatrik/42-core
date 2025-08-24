package solver

import (
	"push_swap_prototype/internal/stack"
)

func easySort(ps *stack.PushSwapData, chunk *stack.Chunk) {
	for chunk.Loc != stack.TOP_A && chunk.Size != 0 {
		if ps.A.GetValueAtPosition(1) == ChunkValue(ps, chunk, 1)+1 && chunk.Size > 0 {
			sortOne(ps, chunk)
		} else if ps.A.GetValueAtPosition(1) == ChunkValue(ps, chunk, 2)+1 && chunk.Size > 1 {
			easySortSecond(ps, chunk)
		} else {
			break
		}
	}
}

func easySortSecond(ps *stack.PushSwapData, chunk *stack.Chunk) {
	switch chunk.Loc {
	case stack.TOP_B:
		handleTopB(ps, chunk)
	case stack.BOTTOM_A:
		handleBottomA(ps, chunk)
	case stack.BOTTOM_B:
		handleBottomB(ps, chunk)
	}
	chunk.Size--
}

func handleTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.Swap_b(ps)
	stack.Push_a(ps)
	
	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
		chunk.Size--
	}
}

func handleBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	stack.Swap_a(ps)
	
	if ps.A.GetValueAtPosition(1) == ps.A.GetValueAtPosition(2)-1 {
		chunk.Size--
	} else {
		stack.Rotate_a(ps)
	}
}

func handleBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
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
