package solver

import (
	"push_swap_prototype/internal/stack"
)

// ChunkSort sorts the entire stack A using chunk-based sorting
func ChunkSort(ps *stack.PushSwapData) {
	
	chunkAll := stack.NewChunk(stack.TOP_A, ps.A.Size())
	RecChunkSort(ps, chunkAll)
}

// RecChunkSort recursively sorts chunks using divide and conquer approach
func RecChunkSort(ps *stack.PushSwapData, toSort *stack.Chunk) {

	EasySort(ps, toSort)

	// FIXED: Use toSort.Size after EasySort, because EasySort now modifies it
	if toSort.Size <= 3 {
		
		switch toSort.Size {
		case 3:
			SortThree(ps, toSort)
		case 2:
			SortTwo(ps, toSort)
		case 1:
			SortOne(ps, toSort)
		default:
			return
		}
		return  // FIXED: Return immediately for small chunks like C implementation
	}
	
	// FIXED: ChunkSplit now returns SplitDest instead of taking a pointer
	dest := ChunkSplit(ps, toSort)
	
	// FIXED: Only recurse on chunks with size > 0 to prevent infinite recursion
	if dest.Max.Size > 0 {
		RecChunkSort(ps, &dest.Max)
	}
	
	if dest.Mid.Size > 0 {
		RecChunkSort(ps, &dest.Mid)
	}
	
	if dest.Min.Size > 0 {
		RecChunkSort(ps, &dest.Min)
	}
}

// SortTwo sorts two elements in a chunk
func SortTwo(ps *stack.PushSwapData, chunk *stack.Chunk) {

	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	}

	if ps.A.GetValue(1) > ps.A.GetValue(2) {
		stack.Swap_a(ps)
	} else {
	}

	// FIXED: Decrement chunk.Size like C implementation
	chunk.Size -= 2
}

// SortOne handles a single element in a chunk
func SortOne(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	} else {
	}
	
	// FIXED: Decrement chunk.Size like C implementation
	chunk.Size--
}
