package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

func EasySort(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	// Early exit if chunk location is TOP_B but Stack B is empty
	if chunk.Loc == stack.TOP_B && ps.B.CurrentSize() == 0 {
		return
	}
	
	// INFINITE LOOP PROTECTION
	iterations := 0
	maxIterations := 1000
	lastChunkSize := chunk.Size
	lastChunkLoc := chunk.Loc
	noChangeCount := 0
	
	fmt.Printf("DEBUG: EasySort START - chunk.Loc=%v, chunk.Size=%d\n", chunk.Loc, chunk.Size)
	
	for chunk.Loc != stack.TOP_A && chunk.Size != 0 {
		iterations++
		
		// INFINITE LOOP DETECTION
		if chunk.Size == lastChunkSize && chunk.Loc == lastChunkLoc {
			noChangeCount++
			if noChangeCount > 10 {
				fmt.Printf("DEBUG: EasySort WARNING - No changes detected for %d iterations! Potential infinite loop!\n", noChangeCount)
				fmt.Printf("DEBUG: EasySort WARNING - chunk.Size=%d, chunk.Loc=%v, breaking loop!\n", chunk.Size, chunk.Loc)
				break
			}
		} else {
			noChangeCount = 0
		}
		
		// MAX ITERATIONS SAFETY
		if iterations > maxIterations {
			fmt.Printf("DEBUG: EasySort WARNING - Max iterations reached (%d)! Potential infinite loop!\n", maxIterations)
			fmt.Printf("DEBUG: EasySort WARNING - chunk.Size=%d, chunk.Loc=%v, breaking loop!\n", chunk.Size, chunk.Loc)
			break
		}
		
		fmt.Printf("DEBUG: EasySort LOOP %d - chunk.Loc=%v, chunk.Size=%d, Stack A top=%d\n", 
			iterations, chunk.Loc, chunk.Size, ps.A.GetValueAtPosition(1))
		
		// Store previous state for change detection
		lastChunkSize = chunk.Size
		lastChunkLoc = chunk.Loc
		
		if ps.A.GetValueAtPosition(1) == ChunkValue(ps, chunk, 1)+1 && chunk.Size > 0 {
			fmt.Printf("DEBUG: EasySort - Condition 1 met, calling SortOne\n")
			SortOne(ps, chunk)
		} else if ps.A.GetValueAtPosition(1) == ChunkValue(ps, chunk, 2)+1 && chunk.Size > 1 {
			fmt.Printf("DEBUG: EasySort - Condition 2 met, calling EasySortSecond\n")
			EasySortSecond(ps, chunk)
		} else {
			fmt.Printf("DEBUG: EasySort - No conditions met, breaking loop\n")
			break
		}
	}
	
	fmt.Printf("DEBUG: EasySort EXIT - chunk.Loc=%v, chunk.Size=%d, total iterations=%d\n", 
		chunk.Loc, chunk.Size, iterations)
}
func EasySortSecond(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	switch chunk.Loc {
	case stack.TOP_B:
		HandleTopB(ps, chunk)
	case stack.BOTTOM_A:
		HandleBottomA(ps, chunk)
	case stack.BOTTOM_B:
		HandleBottomB(ps, chunk)
	}
	
	chunk.Size--
}

func HandleTopB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stack.Swap_b(ps)
	
	stack.Push_a(ps)

	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
	} else {
	}
}

func HandleBottomA(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stack.R_rotate_a(ps)
	stack.R_rotate_a(ps)
	stack.Swap_a(ps)

	if ps.A.GetValueAtPosition(1) == ps.A.GetValueAtPosition(2)-1 {
	} else {
		stack.Rotate_a(ps)
	}
}

func HandleBottomB(ps *stack.PushSwapData, chunk *stack.Chunk) {
	
	stack.R_rotate_b(ps)
	stack.R_rotate_b(ps)
	stack.Push_a(ps)

	if ps.B.GetValueAtPosition(1) == ps.A.GetValueAtPosition(1)-1 {
		stack.Push_a(ps)
	} else {
		stack.Rotate_b(ps)
	}
}
