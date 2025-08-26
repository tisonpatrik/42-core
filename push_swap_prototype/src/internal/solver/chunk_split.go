package solver

import (
	"fmt"
	"push_swap_prototype/internal/stack"
)

// Returns SplitDest instead of modifying a pointer parameter
func ChunkSplit(ps *stack.SortingState, to_split *stack.Chunk, dest *stack.SplitDest) {
	
	fmt.Printf("=== CHUNK_SPLIT START ===\n")
	fmt.Printf("Splitting chunk: loc=%d, size=%d\n", to_split.Loc, to_split.Size)
	
	// Validate input chunk before splitting
	if to_split.Size <= 0 {
		stack.LogError("Invalid chunk size for splitting: %d", to_split.Size)
		return
	}
	
	// Validate stack state before splitting
	result := stack.ValidateStackState(ps, "before ChunkSplit")
	if !result.IsValid {
		stack.LogError("Stack validation failed before ChunkSplit:")
		for _, err := range result.Errors {
			stack.LogError("  - %s", err)
		}
	}
	
	var pivot1, pivot2 int
	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(to_split.Loc, &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(to_split.Loc, to_split.Size, &pivot1, &pivot2)
	
	fmt.Printf("Pivot values: pivot1=%d, pivot2=%d\n", pivot1, pivot2)
	fmt.Printf("Split locations: Min(%d), Mid(%d), Max(%d)\n", dest.Min.Loc, dest.Mid.Loc, dest.Max.Loc)
	fmt.Printf("Stack A before split: top=%d, bottom=%d, current_size=%d\n", ps.A.Top, ps.A.Bottom, stack.GettSize(ps.A))
	fmt.Printf("Stack B before split: top=%d, bottom=%d, current_size=%d\n", ps.B.Top, ps.B.Bottom, stack.GettSize(ps.B))
	fmt.Printf("=== CHUNK POSITIONING ANALYSIS ===\n")
	fmt.Printf("Chunk positioning strategy:\n")
	fmt.Printf("  - MAX chunk goes to loc %d (should end up at TOP_A eventually)\n", dest.Max.Loc)
	fmt.Printf("  - MID chunk goes to loc %d (should end up below MAX chunk)\n", dest.Mid.Loc)
	fmt.Printf("  - MIN chunk goes to loc %d (should end up at bottom)\n", dest.Min.Loc)

	maxValue := ChunkMaxValue(ps, to_split)
	fmt.Printf("Max value in chunk: %d\n", maxValue)
	fmt.Printf("=== ELEMENT DISTRIBUTION ORDER ===\n")

	for i := 0; i < to_split.Size; i++ {
		nextValue := ChunkValue(ps, to_split, 1) // Fixed: Always use index 1 like C implementation
		fmt.Printf("[%d] Processing element %d: value=%d, threshold1=%d, threshold2=%d\n", 
			i+1, i, nextValue, maxValue-pivot1, maxValue-pivot2)

		if nextValue > maxValue-pivot2 {
			fmt.Printf("[%d] Element %d goes to MAX chunk (loc=%d)\n", i+1, nextValue, dest.Max.Loc)
			dest.Max.Size += MoveFromTo(ps, to_split.Loc, dest.Max.Loc)
			SplitMaxReduction(ps, &dest.Max)
			if APartlySort(ps, 1) && to_split.Size-i-1 > 0 {
				fmt.Printf("[%d] Calling EasySort after SplitMaxReduction\n", i+1)
				EasySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			fmt.Printf("[%d] Element %d goes to MID chunk (loc=%d)\n", i+1, nextValue, dest.Mid.Loc)
			dest.Mid.Size += MoveFromTo(ps, to_split.Loc, dest.Mid.Loc)
		} else {
			fmt.Printf("[%d] Element %d goes to MIN chunk (loc=%d)\n", i+1, nextValue, dest.Min.Loc)
			dest.Min.Size += MoveFromTo(ps, to_split.Loc, dest.Min.Loc)
		}
	}
	
	// Validate chunk sizes after distribution
	fmt.Printf("=== CHUNK SIZE VALIDATION ===\n")
	fmt.Printf("Expected total size: %d\n", to_split.Size)
	fmt.Printf("Actual sizes: Max=%d, Mid=%d, Min=%d\n", dest.Max.Size, dest.Mid.Size, dest.Min.Size)
	
	totalDistributed := dest.Max.Size + dest.Mid.Size + dest.Min.Size
	if totalDistributed != to_split.Size {
		stack.LogError("Chunk size mismatch: expected %d, distributed %d", to_split.Size, totalDistributed)
		stack.LogError("  - Max: %d, Mid: %d, Min: %d", dest.Max.Size, dest.Mid.Size, dest.Min.Size)
	}
	
	// Check for empty MID chunk (this is the bug we're investigating)
	if dest.Mid.Size == 0 {
		stack.LogWarning("MID chunk has size 0 - this may cause assembly issues")
		stack.LogWarning("  - Max chunk: loc=%d, size=%d", dest.Max.Loc, dest.Max.Size)
		stack.LogWarning("  - Mid chunk: loc=%d, size=%d", dest.Mid.Loc, dest.Mid.Size)
		stack.LogWarning("  - Min chunk: loc=%d, size=%d", dest.Min.Loc, dest.Min.Size)
	}
	
	fmt.Printf("=== FINAL DISTRIBUTION ===\n")
	fmt.Printf("Final split sizes: Max=%d, Mid=%d, Min=%d\n", dest.Max.Size, dest.Mid.Size, dest.Min.Size)
	fmt.Printf("Stack A after split: top=%d, bottom=%d, current_size=%d\n", ps.A.Top, ps.A.Bottom, stack.GettSize(ps.A))
	fmt.Printf("Stack B after split: top=%d, bottom=%d, current_size=%d\n", ps.B.Top, ps.B.Bottom, stack.GettSize(ps.B))
	fmt.Printf("=== CHUNK POSITIONING AFTER SPLIT ===\n")
	fmt.Printf("Chunk positioning after split:\n")
	fmt.Printf("  - MAX chunk: loc=%d, size=%d (should be processed first)\n", dest.Max.Loc, dest.Max.Size)
	fmt.Printf("  - MID chunk: loc=%d, size=%d (should be processed second)\n", dest.Mid.Loc, dest.Mid.Size)
	fmt.Printf("  - MIN chunk: loc=%d, size=%d (should be processed last)\n", dest.Min.Loc, dest.Min.Size)
	fmt.Printf("  - Processing order: MAX(%d) -> MID(%d) -> MIN(%d)\n", dest.Max.Loc, dest.Mid.Loc, dest.Min.Loc)
	fmt.Printf("=== CHUNK_SPLIT END ===\n")
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
