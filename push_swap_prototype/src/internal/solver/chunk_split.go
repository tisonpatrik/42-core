package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// ChunkSplit splits a chunk into three parts based on pivot values
// Returns SplitDest instead of modifying a pointer parameter
func ChunkSplit(ps *stack.PushSwapData, to_split *stack.Chunk) stack.SplitDest {
	fmt.Printf("DEBUG: ChunkSplit START - to_split.Loc=%v, to_split.Size=%d\n", to_split.Loc, to_split.Size)
	
	var dest stack.SplitDest
	var pivot1, pivot2 int
	var maxValue int

	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)
	maxValue = ChunkMaxValue(ps, to_split)

	fmt.Printf("DEBUG: ChunkSplit - pivots: pivot1=%d, pivot2=%d, maxValue=%d\n", pivot1, pivot2, maxValue)
	fmt.Printf("DEBUG: ChunkSplit - starting loop with to_split.Size=%d\n", to_split.Size)
	originalSize := to_split.Size
	
	for originalSize > 0 {
		originalSize--
		
		fmt.Printf("DEBUG: ChunkSplit LOOP - originalSize=%d, to_split.Size=%d\n", originalSize, to_split.Size)
		
		nextValue := ChunkValue(ps, to_split, 1, originalSize)
		
		fmt.Printf("DEBUG: ChunkSplit - nextValue=%d\n", nextValue)
		
		if nextValue > maxValue-pivot2 {
			fmt.Printf("DEBUG: ChunkSplit - adding to dest.Max\n")
			dest.Max.Size += MoveFromTo(ps, to_split.Loc, dest.Max.Loc)
			SplitMaxReduction(ps, &dest.Max)
			
			if APartlySort(ps, 1) && to_split.Size > 0 {
				fmt.Printf("DEBUG: ChunkSplit - calling EasySort with to_split\n")
				EasySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			fmt.Printf("DEBUG: ChunkSplit - adding to dest.Mid\n")
			dest.Mid.Size += MoveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			fmt.Printf("DEBUG: ChunkSort - adding to dest.Min\n")
			dest.Min.Size += MoveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
	}
	
	fmt.Printf("DEBUG: ChunkSplit END - final sizes: MIN=%d, MID=%d, MAX=%d\n", dest.Min.Size, dest.Mid.Size, dest.Max.Size)
	
	return dest
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
func setThirdPivots(loc stack.Loc, crt_size int, pivot1, pivot2 *int) {
	// CRITICAL FIX: Use SIZE-BASED pivots like C implementation, not VALUE-BASED
	// Initialize pivot_2 first (matches C: *pivot_2 = crt_size / 3)
	*pivot2 = crt_size / 3
	
	// Initialize pivot_1 based on location (matches C implementation exactly)
	switch loc {
	case stack.TOP_A, stack.BOTTOM_A:
		*pivot1 = 2 * crt_size / 3
		// Special case for small chunks (matches C: if (crt_size < 15) *pivot_1 = crt_size)
		if crt_size < 15 {
			*pivot1 = crt_size
		}
	case stack.TOP_B, stack.BOTTOM_B:
		*pivot1 = crt_size / 2
		// Special case for bottom B with small chunks (matches C: if (loc == BOTTOM_B && crt_size < 8) *pivot_2 = crt_size / 2)
		if loc == stack.BOTTOM_B && crt_size < 8 {
			*pivot2 = crt_size / 2
		}
	default:
		// Fallback initialization for any unexpected location values
		*pivot1 = crt_size / 2
	}
	
}
