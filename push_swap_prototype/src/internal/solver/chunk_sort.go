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
	easySort(ps, toSort)
	
	if toSort.Size <= 3 {
		switch toSort.Size {
		case 3:
			sortThree(ps, toSort)
		case 2:
			SortTwo(ps, toSort)
		case 1:
			SortOne(ps, toSort)
		default:
			return
		}
	}

	var dest stack.SplitDest
	ChunkSplit(ps, toSort, &dest)
	
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

