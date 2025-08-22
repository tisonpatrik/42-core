package solver

import (
	"push_swap_prototype/internal/stack"
)

// chunk_sort sorts the entire stack A using chunk-based sorting
func chunk_sort(ps *stack.PushSwapData) {	
	chunkAll := stack.Chunk{
		Loc:  stack.TOP_A, 
		Size: ps.A.Size(),
	}
	
	recChunkSort(ps, &chunkAll)
}

// recChunkSort recursively sorts chunks using divide and conquer approach
func recChunkSort(ps *stack.PushSwapData, toSort *stack.Chunk) {
	chunkToTheTop(ps, toSort)
	easySort(ps, toSort)
	
	if toSort.Size <= 3 {
		switch toSort.Size {
		case 3:
			sortThree(ps, toSort)
		case 2:
			sortTwo(ps, toSort)
		case 1:
			sortOne(ps, toSort)
		default:
			return
		}
	}

	var dest stack.SplitDest
	chunkSplit(ps, toSort, &dest)
	
	recChunkSort(ps, &dest.Max)
	recChunkSort(ps, &dest.Mid)
	recChunkSort(ps, &dest.Min)
}

// sortTwo sorts two elements in a chunk
func sortTwo(ps *stack.PushSwapData, chunk *stack.Chunk) {

	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		moveFromTo(ps, chunk.Loc, stack.TOP_A)
		moveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	
	if ps.A.GetValueAtPosition(1) > ps.A.GetValueAtPosition(2) {
		stack.Swap_a(ps)
	}
	
	chunk.Size -= 2
}

// sortOne handles a single element in a chunk
func sortOne(ps *stack.PushSwapData, chunk *stack.Chunk) {
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		moveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	chunk.Size--
}

