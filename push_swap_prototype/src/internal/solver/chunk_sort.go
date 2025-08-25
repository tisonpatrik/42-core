package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// ChunkSort sorts the entire stack A using chunk-based sorting
func ChunkSort(ps *stack.PushSwapData) {
	chunkAll := stack.Chunk{
		Loc:  stack.TOP_A,
		Size: ps.A.Size(),
	}
	RecChunkSort(ps, &chunkAll)
}

// RecChunkSort recursively sorts chunks using divide and conquer approach
func RecChunkSort(ps *stack.PushSwapData, toSort *stack.Chunk) {

	EasySort(ps, toSort)

	// FIXED: Use toSort.Size after EasySort, because EasySort now modifies it
	if toSort.Size <= 3 {
		fmt.Printf("DEBUG: RecChunkSort - Size <= 3, processing directly\n")
		switch toSort.Size {
		case 3:
			fmt.Printf("DEBUG: RecChunkSort - Calling SortThree\n")
			SortThree(ps, toSort)
		case 2:
			fmt.Printf("DEBUG: RecChunkSort - Calling SortTwo\n")
			SortTwo(ps, toSort)
		case 1:
			fmt.Printf("DEBUG: RecChunkSort - Calling SortOne\n")
			SortOne(ps, toSort)
		default:
			fmt.Printf("DEBUG: RecChunkSort - Size <= 0, returning\n")
			return
		}
		fmt.Printf("DEBUG: RecChunkSort - Returning after sorting small chunk\n")
		return  // FIXED: Return immediately for small chunks like C implementation
	}

	fmt.Printf("DEBUG: RecChunkSort - BEFORE ChunkSplit call\n")
	
	// FIXED: ChunkSplit now returns SplitDest instead of taking a pointer
	dest := ChunkSplit(ps, toSort)
	
	fmt.Printf("DEBUG: RecChunkSort - AFTER ChunkSplit call\n")

	fmt.Printf("DEBUG: RecChunkSort - Calling RecChunkSort with dest.Max\n")
	RecChunkSort(ps, &dest.Max)

	fmt.Printf("DEBUG: RecChunkSort - Calling RecChunkSort with dest.Mid\n")
	RecChunkSort(ps, &dest.Mid)

	fmt.Printf("DEBUG: RecChunkSort - Calling RecChunkSort with dest.Min\n")
	RecChunkSort(ps, &dest.Min)
	
	fmt.Printf("DEBUG: RecChunkSort - END of recursive calls\n")
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

	// FIXED: Decrement chunk.Size like C implementation
	chunk.Size -= 2
}

// SortOne handles a single element in a chunk
func SortOne(ps *stack.PushSwapData, chunk *stack.Chunk) {
	if chunk.Loc == stack.BOTTOM_A || chunk.Loc == stack.BOTTOM_B || chunk.Loc == stack.TOP_B {
		MoveFromTo(ps, chunk.Loc, stack.TOP_A)
	}
	// FIXED: Decrement chunk.Size like C implementation
	chunk.Size--
}
