package solver

import (
	"push_swap_prototype/internal/operations"
)

// chunk_split splits a chunk into three parts based on pivot values
func chunk_split(ps *operations.PushSwapData, to_split *operations.Chunk, dest *operations.SplitDest) {
	var pivot1, pivot2 int
	var maxValue int

	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)
	maxValue = chunkMaxValue(ps, to_split)
	
	// Exactly like C implementation: while (to_split->size--)
	for to_split.Size > 0 {
		nextValue := chunkValue(ps, to_split, 1)
		
		if nextValue > maxValue-pivot2 {
			// Move to max chunk
			dest.Max.Size += moveFromTo(ps, to_split.Loc, dest.Max.Loc)
			splitMaxReduction(ps, &dest.Max)
			if aPartlySort(ps, 1) && to_split.Size > 0 {
				// Apply easy sort optimization exactly like C
				easySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			// Move to mid chunk
			dest.Mid.Size += moveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			// Move to min chunk
			dest.Min.Size += moveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
		to_split.Size-- // Decrement size like C implementation
	}
}

// initSize initializes the size of all destination chunks to 0
func initSize(min, mid, max *operations.Chunk) {
	min.Size = 0
	mid.Size = 0
	max.Size = 0
}

// setSplitLoc sets the location for each destination chunk based on the source location
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
func setThirdPivots(loc operations.Loc, crtSize int, pivot1, pivot2 *int) {
	*pivot2 = crtSize / 3
	
	if loc == operations.TOP_A || loc == operations.BOTTOM_A {
		*pivot1 = 2 * crtSize / 3
		if crtSize < 15 {
			*pivot1 = crtSize // Exactly like C implementation
		}
	}
	if loc == operations.TOP_B || loc == operations.BOTTOM_B {
		*pivot1 = crtSize / 2
	}
	if loc == operations.BOTTOM_B && crtSize < 8 {
		*pivot2 = crtSize / 2
	}
}

// splitMaxReduction reduces the max chunk size when elements are moved
func splitMaxReduction(ps *operations.PushSwapData, max *operations.Chunk) {
	a := ps.A
	
	// Use 1-based indexing like C implementation
	if max.Loc == operations.TOP_A && max.Size == 3 && isConsecutive(
		a.GetValueAtPosition(1), a.GetValueAtPosition(2), 
		a.GetValueAtPosition(3), a.GetValueAtPosition(4)) && 
		aPartlySort(ps, 4) {
		sortThree(ps, max)
		return
	}
	
	if max.Loc == operations.TOP_A && a.GetValueAtPosition(1) == a.GetValueAtPosition(3)-1 && 
		aPartlySort(ps, 3) {
		operations.Swap_a(ps)
		max.Size--
	}
	
	if max.Loc == operations.TOP_A && aPartlySort(ps, 1) {
		max.Size--
	}
}






