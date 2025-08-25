package solver

import (
	"push_swap_prototype/internal/stack"
)

func EasySort(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	// Early exit if chunk location is TOP_B but Stack B is empty
	if chunk.Loc == stack.TOP_B && ps.B.CurrentSize() == 0 {
		return
	}
	
	// INFINITE LOOP PROTECTION
	iterations := 0
	maxIterations := 1000
	lastChunkSize := chunk.Size
	lastChunkLoc := chunk.Loc
	noChangeCount := 0
	
	
	for chunk.Loc != stack.TOP_A && chunk.Size != 0 {
		iterations++
		
		// INFINITE LOOP DETECTION
		if chunk.Size == lastChunkSize && chunk.Loc == lastChunkLoc {
			noChangeCount++
			if noChangeCount > 10 {
				break
			}
		} else {
			noChangeCount = 0
		}
		
		// MAX ITERATIONS SAFETY
		if iterations > maxIterations {
			break
		}
		
		// Store previous state for change detection
		lastChunkSize = chunk.Size
		lastChunkLoc = chunk.Loc
		
		if ps.A.GetValue(1) == ChunkValue(ps, chunk, 1)+1 && chunk.Size > 0 {
			SortOne(ps, chunk)
			// SortOne will decrement chunk.Size
		} else if ps.A.GetValue(1) == ChunkValue(ps, chunk, 2)+1 && chunk.Size > 1 {
			EasySortSecond(ps, chunk)
			// EasySortSecond will decrement chunk.Size
		} else {
			break // FIXED: Add break statement like C implementation
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
	
	// FIXED: Decrement chunk.Size like C implementation
	chunk.Size--
}

func HandleTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stack.Swap_b(ps)
	
	stack.Push_a(ps)

	if ps.B.GetValue(1) == ps.A.GetValue(1)-1 {
		stack.Push_a(ps)
	} else {
	}
}

func HandleBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	stack.Swap_a(ps)

	if ps.A.GetValue(1) == ps.A.GetValue(2)-1 {
	} else {
		stack.Rotate_a(ps)
	}
}

func HandleBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	stack.Push_a(ps)

	if ps.B.GetValue(1) == ps.A.GetValue(1)-1 {
		stack.Push_a(ps)
	} else {
		stack.Rotate_b(ps)
	}
}

