package solver

import (
	"push_swap_prototype/internal/stack"
)

// ChunkSplit splits a chunk into three parts based on pivot values
// Exactly like C implementation
func ChunkSplit(ps *stack.PushSwapData, to_split *stack.Chunk, dest *stack.SplitDest) {
	var pivot1, pivot2 int
	var maxValue int

	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split, &pivot1, &pivot2)
	maxValue = ChunkMaxValue(ps, to_split)


	for to_split.Size > 0 {
						
		nextValue := ChunkValue(ps, to_split, 1)
		
		
		if nextValue > maxValue-pivot2 {
			dest.Max.Size += MoveFromTo(ps, to_split.Loc, dest.Max.Loc)
			SplitMaxReduction(ps, &dest.Max)
			
			if APartlySort(ps, 1) && to_split.Size > 0 {
				EasySort(ps, &dest.Max)
			}
		} else if nextValue > maxValue-pivot1 {
			dest.Mid.Size += MoveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			dest.Min.Size += MoveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
		
		to_split.Size--
	}
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
// Fixed: Now matches C implementation exactly - uses SIZE-BASED pivots, not VALUE-BASED
func setThirdPivots(to_split *stack.Chunk, pivot1, pivot2 *int) {
	// CRITICAL FIX: Use SIZE-BASED pivots like C implementation, not VALUE-BASED
	// Initialize pivot_2 first (matches C: *pivot_2 = crt_size / 3)
	*pivot2 = to_split.Size / 3
	
	// Initialize pivot_1 based on location (matches C implementation exactly)
	switch to_split.Loc {
	case stack.TOP_A, stack.BOTTOM_A:
		*pivot1 = 2 * to_split.Size / 3
		// Special case for small chunks (matches C: if (crt_size < 15) *pivot_1 = crt_size)
		if to_split.Size < 15 {
			*pivot1 = to_split.Size
		}
	case stack.TOP_B, stack.BOTTOM_B:
		*pivot1 = to_split.Size / 2
		// Special case for bottom B with small chunks (matches C: if (loc == BOTTOM_B && crt_size < 8) *pivot_2 = crt_size / 2)
		if to_split.Loc == stack.BOTTOM_B && to_split.Size < 8 {
			*pivot2 = to_split.Size / 2
		}
	default:
		// Fallback initialization for any unexpected location values
		*pivot1 = to_split.Size / 2
	}
	
}
