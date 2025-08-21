package solver

import (
	"push_swap_prototype/internal/operations"
)

// chunk_sort sorts the entire stack A using chunk-based sorting
func chunk_sort(ps *operations.PushSwapData) {
	chunkAll := operations.Chunk{
		Loc:  operations.TOP_A,
		Size: ps.A.Size(),
	}
	
	recChunkSort(ps, &chunkAll)
}

// recChunkSort recursively sorts chunks using divide and conquer approach
func recChunkSort(ps *operations.PushSwapData, toSort *operations.Chunk) {
	// Move chunk to the top if needed
	chunkToTheTop(ps, toSort)
	
	// Apply easy sort optimization
	easySort(ps, toSort)
	
	// Handle small chunks with direct sorting
	if toSort.Size <= 3 {
		switch toSort.Size {
		case 3:
			sortThree(ps, toSort)
		case 2:
			sortTwo(ps, toSort)
		case 1:
			sortOne(ps, toSort)
		}
		return
	}
	
	// Split chunk and recursively sort
	var dest operations.SplitDest
	chunk_split(ps, toSort, &dest)
	
	// Recursively sort the three parts (exactly like C implementation)
	recChunkSort(ps, &dest.Max)
	recChunkSort(ps, &dest.Mid)
	recChunkSort(ps, &dest.Min)
}

// sortTwo sorts two elements in a chunk
func sortTwo(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// Move elements to TOP_A if they're not already there (exactly like C implementation)
	if chunk.Loc == operations.BOTTOM_A || chunk.Loc == operations.BOTTOM_B || chunk.Loc == operations.TOP_B {
		moveFromTo(ps, chunk.Loc, operations.TOP_A)
		moveFromTo(ps, chunk.Loc, operations.TOP_A)
	}
	
	// If the top element is greater than the second element, swap them
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) > ps.A.GetValueAtPosition(2) {
		operations.Swap_a(ps)
	}
	
	chunk.Size -= 2
}

// sortOne handles a single element in a chunk
func sortOne(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// Move element to TOP_A if it's not already there
	if chunk.Loc == operations.BOTTOM_A || chunk.Loc == operations.BOTTOM_B || chunk.Loc == operations.TOP_B {
		moveFromTo(ps, chunk.Loc, operations.TOP_A)
	}
	chunk.Size--
}

