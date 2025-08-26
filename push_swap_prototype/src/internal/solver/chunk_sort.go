package solver

import (
	"push_swap_prototype/internal/stack"
)

// ChunkSort sorts the entire stack A using chunk-based sorting
func ChunkSort(ps *stack.SortingState) {
	
	chunkAll := stack.Chunk{Loc: stack.TOP_A, Size: stack.GettSize(ps.A)}
	RecChunkSort(ps, &chunkAll)
}

// RecChunkSort recursively sorts chunks using divide and conquer approach
func RecChunkSort(ps *stack.SortingState, toSort *stack.Chunk) {
	
	ChunkToTheTop(ps, toSort)
	EasySort(ps, toSort)
	
	if toSort.Size <= 3 {
		
		switch toSort.Size {
		case 3:
			SortThree(ps, toSort)
		case 2:
			SortTwo(ps, toSort)
		case 1:
			SortOne(ps, toSort)
		}
		return
	}
	
	var dest stack.SplitDest
	ChunkSplit(ps, toSort, &dest)
	
	RecChunkSort(ps, &dest.Max)
	RecChunkSort(ps, &dest.Mid)
	RecChunkSort(ps, &dest.Min)
}

// SortTwo sorts two elements in a chunk
func SortTwo(ps *stack.SortingState, chunk *stack.Chunk) {

	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	}

	if stack.Value(ps.A, 1) > stack.Value(ps.A, 2) {
		stack.SwapA(ps)
	}

	chunk.Size -= 2
}

// SortOne handles a single element in a chunk
func SortOne(ps *stack.SortingState, to_sort *stack.Chunk) {
	
	if to_sort.Loc == stack.BOTTOM_A || to_sort.Loc == stack.BOTTOM_B || to_sort.Loc == stack.TOP_B {
		MoveFromTo(ps, to_sort.Loc, stack.TOP_A)
	}
	
	to_sort.Size -= 1
}