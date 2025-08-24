package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// ChunkSplit splits a chunk into three parts based on pivot values
// Exactly like C implementation
func ChunkSplit(ps *stack.PushSwapData, to_split *stack.Chunk, dest *stack.SplitDest) {
	var pivot1, pivot2 int
	var maxValue int

	fmt.Printf("DEBUG: ChunkSplit START - to_split: loc=%v, size=%d\n", to_split.Loc, to_split.Size)

	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)
	maxValue = ChunkMaxValue(ps, to_split)

	fmt.Printf("DEBUG: ChunkSplit - pivots: pivot1=%d, pivot2=%d, maxValue=%d\n", pivot1, pivot2, maxValue)
	fmt.Printf("DEBUG: ChunkSplit - dest locations: MIN=%v, MID=%v, MAX=%v\n", dest.Min.Loc, dest.Mid.Loc, dest.Max.Loc)

	for to_split.Size > 0 {
		oldSize := to_split.Size
		to_split.Size--
		nextValue := ChunkValue(ps, to_split, 1)

		fmt.Printf("DEBUG: ChunkSplit LOOP - to_split.Size: %d->%d, nextValue=%d\n", oldSize, to_split.Size, nextValue)

		if nextValue > maxValue-pivot2 {
			fmt.Printf("DEBUG: ChunkSplit - Moving to MAX chunk (dest.Max.Size: %d->", dest.Max.Size)
			// FIXED: Store MoveFromTo result before calling SplitMaxReduction
			moved := MoveFromTo(ps, to_split.Loc, dest.Max.Loc)
			dest.Max.Size += moved
			fmt.Printf("%d), moved=%d\n", dest.Max.Size, moved)

			// SplitMaxReduction should be called on dest.Max, as in C implementation
			fmt.Printf("DEBUG: ChunkSplit - Calling SplitMaxReduction on dest.Max (size=%d)\n", dest.Max.Size)
			SplitMaxReduction(ps, &dest.Max)
			fmt.Printf("DEBUG: ChunkSplit - After SplitMaxReduction: dest.Max.Size=%d\n", dest.Max.Size)

			if APartlySort(ps, 1) && to_split.Size > 0 {
				fmt.Printf("DEBUG: ChunkSplit - Calling easySort on to_split (size=%d)\n", to_split.Size)
				EasySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			fmt.Printf("DEBUG: ChunkSplit - Moving to MID chunk (dest.Mid.Size: %d->", dest.Mid.Size)
			dest.Mid.Size += MoveFromTo(ps, to_split.Loc, dest.Mid.Loc)
			fmt.Printf("%d)\n", dest.Mid.Size)
		} else {
			fmt.Printf("DEBUG: ChunkSplit - Moving to MIN chunk (dest.Min.Size: %d->", dest.Min.Size)
			dest.Min.Size += MoveFromTo(ps, to_split.Loc, dest.Min.Loc)
			fmt.Printf("%d)\n", dest.Min.Size)
		}
	}

	fmt.Printf("DEBUG: ChunkSplit END - Final sizes: MIN=%d, MID=%d, MAX=%d\n", dest.Min.Size, dest.Mid.Size, dest.Max.Size)
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
	*pivot1 = crtSize / 2
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
