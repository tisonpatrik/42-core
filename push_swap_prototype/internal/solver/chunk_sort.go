package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// chunk_sort sorts the entire stack A using chunk-based sorting
func chunk_sort(ps *stack.PushSwapData) {
	fmt.Printf("=== CHUNK_SORT START ===\n")
	fmt.Printf("Initial stack A size: %d\n", ps.A.Size())
	
	chunkAll := stack.Chunk{
		Loc:  stack.TOP_A, 
		Size: ps.A.Size(),
	}
	
	fmt.Printf("Initial chunk: loc=%v, size=%d\n", chunkAll.Loc, chunkAll.Size)
	recChunkSort(ps, &chunkAll)
	fmt.Printf("=== CHUNK_SORT END ===\n")
}

// recChunkSort recursively sorts chunks using divide and conquer approach
func recChunkSort(ps *stack.PushSwapData, toSort *stack.Chunk) {
	fmt.Printf("=== REC_CHUNK_SORT ===\n")
	fmt.Printf("Input chunk: loc=%v, size=%d\n", toSort.Loc, toSort.Size)
	fmt.Printf("Stack A size: %d, Stack B size: %d\n", ps.A.Size(), ps.B.Size())
	
	// Move chunk to the top if needed
	chunkToTheTop(ps, toSort)
	
	// Apply easy sort optimization
	easySort(ps, toSort)
	
	// Check if chunk size was reduced to <= 3 by easySort
	if toSort.Size <= 3 {
		fmt.Printf("Chunk size reduced to %d by easySort, handling directly\n", toSort.Size)
		// Handle small chunks with direct sorting
		switch toSort.Size {
		case 3:
			fmt.Printf("Sorting 3 elements\n")
			sortThree(ps, toSort)
		case 2:
			fmt.Printf("Sorting 2 elements\n")
			sortTwo(ps, toSort)
		case 1:
			fmt.Printf("Sorting 1 element\n")
			sortOne(ps, toSort)
		case 0:
			fmt.Printf("Chunk is empty, nothing to sort\n")
		}
		fmt.Printf("=== REC_CHUNK_SORT END (small chunk) ===\n")
		return
	}
	
	// Split chunk and recursively sort
	fmt.Printf("Splitting chunk (size > 3)\n")
	
	var dest stack.SplitDest
	chunkSplit(ps, toSort, &dest)
	
	fmt.Printf("After split - Max: %d, Mid: %d, Min: %d\n", 
		dest.Max.Size, dest.Mid.Size, dest.Min.Size)
	
	// Recursively sort the three parts (exactly like C implementation)
	fmt.Printf("Recursively sorting MAX chunk\n")
	recChunkSort(ps, &dest.Max)
	fmt.Printf("Recursively sorting MID chunk\n")
	recChunkSort(ps, &dest.Mid)
	fmt.Printf("Recursively sorting MIN chunk\n")
	recChunkSort(ps, &dest.Min)
	
	fmt.Printf("=== REC_CHUNK_SORT END ===\n")
}

// sortTwo sorts two elements in a chunk
func sortTwo(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("  sortTwo: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	// Move elements to TOP_A if they're not already there (exactly like C implementation)
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		fmt.Printf("    Moving elements to TOP_A\n")
		moveFromTo(ps, chunk.Loc, stack.TOP_A)
		moveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	
	// If the top element is greater than the second element, swap them
	// Use 1-based indexing like C implementation
	if ps.A.GetValueAtPosition(1) > ps.A.GetValueAtPosition(2) {
		fmt.Printf("    Swapping A[0] and A[1]\n")
		stack.Swap_a(ps)
	}
	
	chunk.Size -= 2
	fmt.Printf("    After sortTwo: chunk size=%d\n", chunk.Size)
}

// sortOne handles a single element in a chunk
func sortOne(ps *stack.PushSwapData, chunk *stack.Chunk) {
	fmt.Printf("  sortOne: chunk loc=%v, size=%d\n", chunk.Loc, chunk.Size)
	
	// Move element to TOP_A if it's not already there
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		fmt.Printf("    Moving element to TOP_A\n")
		moveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	chunk.Size--
	fmt.Printf("    After sortOne: chunk size=%d\n", chunk.Size)
}

