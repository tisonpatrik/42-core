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
	
	// FIXED: Match C implementation exactly - call chunk_to_the_top first
	ChunkToTheTop(ps, toSort)
	EasySort(ps, toSort)
	
	if toSort.Size <= 3 {
		
		if toSort.Size == 3 {
			SortThree(ps, toSort)
		} else if toSort.Size == 2 {
			SortTwo(ps, toSort)
		} else if toSort.Size == 1 {
			SortOne(ps, toSort)
		}
		return
	}
	
	// FIXED: Match C implementation exactly - use pointer parameter like C
	var dest stack.SplitDest
	ChunkSplit(ps, toSort, &dest)
	
	// FIXED: Match C implementation exactly - always recurse on all chunks
	RecChunkSort(ps, &dest.Max)
	RecChunkSort(ps, &dest.Mid)
	RecChunkSort(ps, &dest.Min)
}

// SortTwo sorts two elements in a chunk
func SortTwo(ps *stack.PushSwapData, chunk *stack.Chunk) {

	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	}

	// FIXED: Match C implementation exactly - use value() function
	if ps.A.GetValue(1) > ps.A.GetValue(2) {
		stack.Swap_a(ps)
	}

	// FIXED: Match C implementation exactly - decrement size
	chunk.Size -= 2
}

// SortOne handles a single element in a chunk
func SortOne(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	
	// FIXED: Match C implementation exactly - decrement size
	chunk.Size -= 1
}