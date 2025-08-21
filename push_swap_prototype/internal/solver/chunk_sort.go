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

// chunkToTheTop moves the chunk to the top of its stack
func chunkToTheTop(ps *operations.PushSwapData, chunk *operations.Chunk) {
	// Exactly like C implementation - just update location, don't move elements
	if chunk.Loc == operations.BOTTOM_B && ps.B.CurrentSize() == chunk.Size {
		chunk.Loc = operations.TOP_B
	}
	if chunk.Loc == operations.BOTTOM_A && ps.A.CurrentSize() == chunk.Size {
		chunk.Loc = operations.TOP_A
	}
}
