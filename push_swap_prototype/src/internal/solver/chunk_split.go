package solver

import (
	"fmt"
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
)

// Returns SplitDest instead of modifying a pointer parameter
func ChunkSplit(ps *ops.SortingState, to_split *chunk.Chunk, dest *chunk.SplitDest) {
	
	fmt.Printf("=== CHUNK_SPLIT START ===\n")
	fmt.Printf("Splitting chunk: loc=%d, size=%d\n", chunk.GetLoc(to_split), chunk.GetSize(to_split))
	
	
	var pivot1, pivot2 int
	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(chunk.GetLoc(to_split), &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(chunk.GetLoc(to_split), chunk.GetSize(to_split), &pivot1, &pivot2)

	maxValue := ChunkMaxValue(ps, to_split)


	for i := 0; i < chunk.GetSize(to_split); i++ {
		nextValue := ChunkValue(ps, to_split, i) // Use position i, not hardcoded 1

		if nextValue > maxValue-pivot2 {
			chunk.SetSize(&dest.Max, chunk.GetSize(&dest.Max)+MoveFromTo(ps, chunk.GetLoc(to_split), chunk.GetLoc(&dest.Max)))
			SplitMaxReduction(ps, &dest.Max)
			if APartlySort(ps, 1) && chunk.GetSize(to_split)-i-1 > 0 {
				fmt.Printf("[%d] Calling EasySort after SplitMaxReduction\n", i+1)
				EasySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			chunk.SetSize(&dest.Mid, chunk.GetSize(&dest.Mid)+MoveFromTo(ps, chunk.GetLoc(to_split), chunk.GetLoc(&dest.Mid)))
		} else {
			chunk.SetSize(&dest.Min, chunk.GetSize(&dest.Min)+MoveFromTo(ps, chunk.GetLoc(to_split), chunk.GetLoc(&dest.Min)))
		}
	}
}

// initSize initializes the size of all destination chunks to 0
func initSize(min, mid, max *chunk.Chunk) {
	chunk.SetSize(min, 0)
	chunk.SetSize(mid, 0)
	chunk.SetSize(max, 0)
}

// setSplitLoc sets the location for each destination chunk based on the source location
// Exactly like C implementation
func setSplitLoc(loc chunk.Loc, min, mid, max *chunk.Chunk) {
	
	switch loc {
	case chunk.TOP_A:
		chunk.SetLoc(min, chunk.BOTTOM_B)
		chunk.SetLoc(mid, chunk.TOP_B)
		chunk.SetLoc(max, chunk.BOTTOM_A)
	case chunk.BOTTOM_A:
		chunk.SetLoc(min, chunk.BOTTOM_B)
		chunk.SetLoc(mid, chunk.TOP_B)
		chunk.SetLoc(max, chunk.TOP_A)
	case chunk.TOP_B:
		chunk.SetLoc(min, chunk.BOTTOM_B)
		chunk.SetLoc(mid, chunk.BOTTOM_A)
		chunk.SetLoc(max, chunk.TOP_A)
	case chunk.BOTTOM_B:
		chunk.SetLoc(min, chunk.TOP_B)
		chunk.SetLoc(mid, chunk.BOTTOM_A)
		chunk.SetLoc(max, chunk.TOP_A)
	}
}

// setThirdPivots sets the pivot values for splitting based on location and size
func setThirdPivots(loc chunk.Loc, crt_size int, pivot1, pivot2 *int) {
	
	*pivot2 = crt_size / 3
	
	switch loc {
	case chunk.TOP_A, chunk.BOTTOM_A:
		*pivot1 = 2 * crt_size / 3
		// Special case for small chunks (matches C: if (crt_size < 15) *pivot_1 = crt_size)
		if crt_size < 15 {
			*pivot1 = crt_size
		}
	case chunk.TOP_B, chunk.BOTTOM_B:
		*pivot1 = crt_size / 2
		if loc == chunk.BOTTOM_B && crt_size < 8 {
			*pivot2 = crt_size / 2
		}
	default:
		*pivot1 = crt_size / 2
	}
}
