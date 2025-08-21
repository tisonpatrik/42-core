package solver

import (
	"push_swap_prototype/internal/operations"
)

// chunk_split splits a chunk into three parts based on pivot values
// Exactly like C implementation
func chunk_split(ps *operations.PushSwapData, to_split *operations.Chunk, dest *operations.SplitDest) {
	var pivot1, pivot2 int
	var maxValue int

	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)
	maxValue = chunkMaxValue(ps, to_split)
	// Exactly like C implementation: while (to_split->size--)
	for to_split.Size > 0 {
		to_split.Size--
		nextValue := chunkValue(ps, to_split, 1)
		
		if nextValue > maxValue-pivot2 {
			dest.Max.Size += moveFromTo(ps, to_split.Loc, dest.Max.Loc)
			splitMaxReduction(ps, &dest.Max)
			if aPartlySort(ps, 1) && to_split.Size > 0 {
				easySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			dest.Mid.Size += moveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			dest.Min.Size += moveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
	}
}

// initSize initializes the size of all destination chunks to 0
func initSize(min, mid, max *operations.Chunk) {
	min.Size = 0
	mid.Size = 0
	max.Size = 0
}

// setSplitLoc sets the location for each destination chunk based on the source location
// Exactly like C implementation
func setSplitLoc(loc operations.Loc, min, mid, max *operations.Chunk) {
	switch loc {
	case operations.TOP_A:
		min.Loc = operations.BOTTOM_B
		mid.Loc = operations.TOP_B
		max.Loc = operations.BOTTOM_A
	case operations.BOTTOM_A:
		min.Loc = operations.BOTTOM_B
		mid.Loc = operations.TOP_B
		max.Loc = operations.TOP_A
	case operations.TOP_B:
		min.Loc = operations.BOTTOM_B
		mid.Loc = operations.BOTTOM_A
		max.Loc = operations.TOP_A
	case operations.BOTTOM_B:
		min.Loc = operations.TOP_B
		mid.Loc = operations.BOTTOM_A
		max.Loc = operations.TOP_A
	}
}

// setThirdPivots sets the pivot values for splitting based on location and size
// Exactly like C implementation
func setThirdPivots(loc operations.Loc, crtSize int, pivot1, pivot2 *int) {
	*pivot2 = crtSize / 3
	
	switch loc {
	case operations.TOP_A, operations.BOTTOM_A:
		*pivot1 = 2 * crtSize / 3
	case operations.TOP_B, operations.BOTTOM_B:
		*pivot1 = crtSize / 2
	default:
		*pivot1 = crtSize / 2 // Default case to ensure pivot1 is always set
	}
	
	if (loc == operations.TOP_A || loc == operations.BOTTOM_A) && crtSize < 15 {
		*pivot1 = crtSize
	}
	if loc == operations.BOTTOM_B && crtSize < 8 {
		*pivot2 = crtSize / 2
	}
}








