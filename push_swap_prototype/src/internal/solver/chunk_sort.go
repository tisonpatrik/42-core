package solver

import (
	"push_swap_prototype/internal/stack"
)

// Chunk_sort sorts the entire stack A using chunk-based sorting
func Chunk_sort(ps *stack.PushSwapData) {
	chunkAll := stack.Chunk{
		Loc:  stack.TOP_A,
		Size: ps.A.Size(),
	}

	RecChunkSort(ps, &chunkAll)
}

// RecChunkSort recursively sorts chunks using divide and conquer approach
func RecChunkSort(ps *stack.PushSwapData, toSort *stack.Chunk) {
	chunkToTheTop(ps, toSort)
	EasySort(ps, toSort)

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
		return // Return early for small chunks, don't split them
	}

	// Only split chunks larger than 3
	var dest stack.SplitDest
	ChunkSplit(ps, toSort, &dest)

	// Only recurse on chunks with size > 0
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

	if ps.A.GetValueAtPosition(1) > ps.A.GetValueAtPosition(2) {
		stack.Swap_a(ps)
	}

	chunk.Size -= 2
}

// SortOne handles a single element in a chunk
func SortOne(ps *stack.PushSwapData, chunk *stack.Chunk) {
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	chunk.Size--
}
