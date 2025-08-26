package solver

import (
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// ChunkSort sorts the entire stack A using chunk-based sorting
func ChunkSort(ps *ops.SortingState) {
	
	chunkAll := chunk.NewChunk(chunk.TOP_A, stack.GetSize(ps.A))
	
	RecChunkSort(ps, chunkAll)
}

// RecChunkSort recursively sorts chunks using divide and conquer approach
func RecChunkSort(ps *ops.SortingState, toSort *chunk.Chunk) {
	
	ChunkToTheTop(ps, toSort)
	EasySort(ps, toSort)
	
	if chunk.GetSize(toSort) <= 3 {
		
		switch chunk.GetSize(toSort) {
		case 3:
			SortThree(ps, toSort)
		case 2:
			SortTwo(ps, toSort)
		case 1:
			SortOne(ps, toSort)
		}
		return
	}
	
	var dest chunk.SplitDest
	ChunkSplit(ps, toSort, &dest)
	RecChunkSort(ps, &dest.Max)
	RecChunkSort(ps, &dest.Mid)
	RecChunkSort(ps, &dest.Min)
}

// SortTwo sorts two elements in a chunk
func SortTwo(ps *ops.SortingState, to_sort *chunk.Chunk) {

	if chunk.GetLoc(to_sort) == chunk.BOTTOM_A || chunk.GetLoc(to_sort) == chunk.BOTTOM_B || chunk.GetLoc(to_sort) == chunk.TOP_B {
		MoveFromTo(ps, chunk.GetLoc(to_sort), chunk.TOP_A)
		MoveFromTo(ps, chunk.GetLoc(to_sort), chunk.TOP_A)
	}

	if stack.GetValue(ps.A, 1) > stack.GetValue(ps.A, 2) {
		ops.SwapA(ps)
	}

	chunk.SetSize(to_sort, chunk.GetSize(to_sort)-2)
}

// SortOne handles a single element in a chunk
func SortOne(ps *ops.SortingState, to_sort *chunk.Chunk) {
	
	if chunk.GetLoc(to_sort) == chunk.BOTTOM_A || chunk.GetLoc(to_sort) == chunk.BOTTOM_B || chunk.GetLoc(to_sort) == chunk.TOP_B {
		MoveFromTo(ps, chunk.GetLoc(to_sort), chunk.TOP_A)
	}
	
	chunk.SetSize(to_sort, chunk.GetSize(to_sort)-1)
}