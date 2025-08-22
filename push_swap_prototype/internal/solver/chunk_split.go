package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// chunkSplit splits a chunk into three parts based on pivot values
// Exactly like C implementation
func chunkSplit(ps *stack.PushSwapData, to_split *stack.Chunk, dest *stack.SplitDest) {
	var pivot1, pivot2 int
	var maxValue int

	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)
	maxValue = chunkMaxValue(ps, to_split)
	
	// Log initial state
	fmt.Printf("=== CHUNK_SPLIT START ===\n")
	fmt.Printf("Initial size: %d, maxValue: %d, pivot1: %d, pivot2: %d\n", 
		to_split.Size, maxValue, pivot1, pivot2)
	fmt.Printf("Dest locations - Min: %v, Mid: %v, Max: %v\n", 
		dest.Min.Loc, dest.Mid.Loc, dest.Max.Loc)
	
	// Exactly like C implementation: while (to_split->size--)
	for to_split.Size > 0 {
		nextValue := chunkValue(ps, to_split, 1)
		
		fmt.Printf("Processing value: %d (size remaining: %d)\n", nextValue, to_split.Size)
		
		if nextValue > maxValue-pivot2 {
			fmt.Printf("  -> MAX chunk (value %d > %d)\n", nextValue, maxValue-pivot2)
			dest.Max.Size += moveFromTo(ps, to_split.Loc, dest.Max.Loc)
			splitMaxReduction(ps, &dest.Max)
			if aPartlySort(ps, 1) && to_split.Size > 0 {
				easySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			fmt.Printf("  -> MID chunk (value %d > %d)\n", nextValue, maxValue-pivot1)
			dest.Mid.Size += moveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			fmt.Printf("  -> MIN chunk (value %d <= %d)\n", nextValue, maxValue-pivot1)
			dest.Min.Size += moveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
		
		to_split.Size--
	}
	
	fmt.Printf("=== CHUNK_SPLIT END ===\n")
	fmt.Printf("Final sizes - Min: %d, Mid: %d, Max: %d\n", 
		dest.Min.Size, dest.Mid.Size, dest.Max.Size)
}

// initSize initializes the size of all destination chunks to 0
func initSize(min, mid, max *stack.Chunk) {
	min.Size = 0
	mid.Size = 0
	max.Size = 0
}

// setSplitLoc sets the location for each destination chunk based on the source location
// Exactly like C implementation
func setSplitLoc(loc stack.Loc, min, mid, max *stack.Chunk) {
	switch loc {
	case stack.TOP_A:
		min.Loc = stack.BOTTOM_B
		mid.Loc = stack.TOP_B
		max.Loc = stack.BOTTOM_A
	case stack.BOTTOM_A:
		min.Loc = stack.BOTTOM_B
		mid.Loc = stack.TOP_B
		max.Loc = stack.TOP_A
	case stack.TOP_B:
		min.Loc = stack.BOTTOM_B
		mid.Loc = stack.BOTTOM_A
		max.Loc = stack.TOP_A
	case stack.BOTTOM_B:
		min.Loc = stack.TOP_B
		mid.Loc = stack.BOTTOM_A
		max.Loc = stack.TOP_A
	}
}

// setThirdPivots sets the pivot values for splitting based on location and size
// Exactly like C implementation
func setThirdPivots(loc stack.Loc, crtSize int, pivot1, pivot2 *int) {
	*pivot2 = crtSize / 3
	
	switch loc {
	case stack.TOP_A, stack.BOTTOM_A:
		*pivot1 = 2 * crtSize / 3
	case stack.TOP_B, stack.BOTTOM_B:
		*pivot1 = crtSize / 2
	default:
		*pivot1 = crtSize / 2 // Default case to ensure pivot1 is always set
	}
	
	if (loc == stack.TOP_A || loc == stack.BOTTOM_A) && crtSize < 15 {
		*pivot1 = crtSize
	}
	if loc == stack.BOTTOM_B && crtSize < 8 {
		*pivot2 = crtSize / 2
	}
}








