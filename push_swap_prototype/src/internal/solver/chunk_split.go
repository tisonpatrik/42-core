package solver

import (
	"push_swap_prototype/internal/stack"
)

// Returns SplitDest instead of modifying a pointer parameter
func ChunkSplit(ps *stack.PushSwapData, to_split *stack.Chunk, dest *stack.SplitDest) {
	
	var pivot1, pivot2 int
	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)

	maxValue := ChunkMaxValue(ps, to_split)

	for i := 0; i < to_split.Size; i++ {
		nextValue := ChunkValue(ps, to_split, 1) // Fixed: Always use index 1 like C implementation

		if nextValue > maxValue-pivot2 {
			dest.Max.Size += MoveFromTo(ps, to_split.Loc, dest.Max.Loc)
			SplitMaxReduction(ps, &dest.Max)
			if APartlySort(ps, 1) && to_split.Size-i-1 > 0 {
				EasySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			dest.Mid.Size += MoveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			dest.Min.Size += MoveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
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
func setThirdPivots(loc stack.Loc, crt_size int, pivot1, pivot2 *int) {
	
	*pivot2 = crt_size / 3
	
	switch loc {
	case stack.TOP_A, stack.BOTTOM_A:
		*pivot1 = 2 * crt_size / 3
		// Special case for small chunks (matches C: if (crt_size < 15) *pivot_1 = crt_size)
		if crt_size < 15 {
			*pivot1 = crt_size
		}
	case stack.TOP_B, stack.BOTTOM_B:
		*pivot1 = crt_size / 2
		if loc == stack.BOTTOM_B && crt_size < 8 {
			*pivot2 = crt_size / 2
		}
	default:
		*pivot1 = crt_size / 2
	}
}
