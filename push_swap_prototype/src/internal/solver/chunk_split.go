package solver

import (
	"fmt"
	"push_swap_prototype/internal/chunk"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/stack"
)

// Returns SplitDest instead of modifying a pointer parameter
func ChunkSplit(ps *ops.SortingState, to_split *chunk.Chunk, dest *chunk.SplitDest) {
	
	fmt.Printf("=== CHUNK_SPLIT START ===\n")
	fmt.Printf("Splitting chunk: loc=%d, size=%d\n", chunk.GetLoc(to_split), chunk.GetSize(to_split))
	
	// Validate input chunk before splitting
	if chunk.GetSize(to_split) <= 0 {
		ops.LogError("Invalid chunk size for splitting: %d", chunk.GetSize(to_split))
		return
	}
	
	// Validate stack state before splitting
	result := ops.ValidateStackState(ps, "before ChunkSplit")
	if !result.IsValid {
		ops.LogError("Stack validation failed before ChunkSplit:")
		for _, err := range result.Errors {
			ops.LogError("  - %s", err)
		}
	}
	
	var pivot1, pivot2 int
	initSize(&dest.Min, &dest.Mid, &dest.Max)
	setSplitLoc(chunk.GetLoc(to_split), &dest.Min, &dest.Mid, &dest.Max)
	setThirdPivots(chunk.GetLoc(to_split), chunk.GetSize(to_split), &pivot1, &pivot2)
	
	fmt.Printf("Pivot values: pivot1=%d, pivot2=%d\n", pivot1, pivot2)
	fmt.Printf("Split locations: Min(%d), Mid(%d), Max(%d)\n", chunk.GetLoc(&dest.Min), chunk.GetLoc(&dest.Mid), chunk.GetLoc(&dest.Max))
	fmt.Printf("Stack A before split: top=%d, bottom=%d, current_size=%d\n", stack.GetTop(ps.A), stack.GetBottom(ps.A), stack.GetSize(ps.A))
	fmt.Printf("Stack B before split: top=%d, bottom=%d, current_size=%d\n", stack.GetTop(ps.B), stack.GetBottom(ps.B), stack.GetSize(ps.B))
	fmt.Printf("=== CHUNK POSITIONING ANALYSIS ===\n")
	fmt.Printf("Chunk positioning strategy:\n")
	fmt.Printf("  - MAX chunk goes to loc %d (should end up at TOP_A eventually)\n", chunk.GetLoc(&dest.Max))
	fmt.Printf("  - MID chunk goes to loc %d (should end up below MAX chunk)\n", chunk.GetLoc(&dest.Mid))
	fmt.Printf("  - MIN chunk goes to loc %d (should end up at bottom)\n", chunk.GetLoc(&dest.Min))

	maxValue := ChunkMaxValue(ps, to_split)
	fmt.Printf("Max value in chunk: %d\n", maxValue)
	fmt.Printf("=== ELEMENT DISTRIBUTION ORDER ===\n")

	for i := 0; i < chunk.GetSize(to_split); i++ {
		nextValue := ChunkValue(ps, to_split, i) // Use position i, not hardcoded 1
		fmt.Printf("[%d] Processing element %d: value=%d, threshold1=%d, threshold2=%d\n", 
			i+1, i, nextValue, maxValue-pivot1, maxValue-pivot2)

		if nextValue > maxValue-pivot2 {
			fmt.Printf("[%d] Element %d goes to MAX chunk (loc=%d)\n", i+1, nextValue, chunk.GetLoc(&dest.Max))
			chunk.SetSize(&dest.Max, chunk.GetSize(&dest.Max)+MoveFromTo(ps, chunk.GetLoc(to_split), chunk.GetLoc(&dest.Max)))
			SplitMaxReduction(ps, &dest.Max)
			if APartlySort(ps, 1) && chunk.GetSize(to_split)-i-1 > 0 {
				fmt.Printf("[%d] Calling EasySort after SplitMaxReduction\n", i+1)
				EasySort(ps, to_split)
			}
		} else if nextValue > maxValue-pivot1 {
			fmt.Printf("[%d] Element %d goes to MID chunk (loc=%d)\n", i+1, nextValue, chunk.GetLoc(&dest.Mid))
			chunk.SetSize(&dest.Mid, chunk.GetSize(&dest.Mid)+MoveFromTo(ps, chunk.GetLoc(to_split), chunk.GetLoc(&dest.Mid)))
		} else {
			fmt.Printf("[%d] Element %d goes to MIN chunk (loc=%d)\n", i+1, nextValue, chunk.GetLoc(&dest.Min))
			chunk.SetSize(&dest.Min, chunk.GetSize(&dest.Min)+MoveFromTo(ps, chunk.GetLoc(to_split), chunk.GetLoc(&dest.Min)))
		}
	}
	
	// Validate chunk sizes after distribution
	fmt.Printf("=== CHUNK SIZE VALIDATION ===\n")
	fmt.Printf("Expected total size: %d\n", chunk.GetSize(to_split))
	fmt.Printf("Actual sizes: Max=%d, Mid=%d, Min=%d\n", chunk.GetSize(&dest.Max), chunk.GetSize(&dest.Mid), chunk.GetSize(&dest.Min))
	
	totalDistributed := chunk.GetSize(&dest.Max) + chunk.GetSize(&dest.Mid) + chunk.GetSize(&dest.Min)
	if totalDistributed != chunk.GetSize(to_split) {
		ops.LogError("Chunk size mismatch: expected %d, distributed %d", chunk.GetSize(to_split), totalDistributed)
		ops.LogError("  - Max: %d, Mid: %d, Min: %d", chunk.GetSize(&dest.Max), chunk.GetSize(&dest.Mid), chunk.GetSize(&dest.Min))
	}
	
	// Check for empty MID chunk (this is the bug we're investigating)
	if chunk.GetSize(&dest.Mid) == 0 {
		ops.LogWarning("MID chunk has size 0 - this may cause assembly issues")
		ops.LogWarning("  - Max chunk: loc=%d, size=%d", chunk.GetLoc(&dest.Max), chunk.GetSize(&dest.Max))
		ops.LogWarning("  - Mid chunk: loc=%d, size=%d", chunk.GetLoc(&dest.Mid), chunk.GetSize(&dest.Mid))
		ops.LogWarning("  - Min chunk: loc=%d, size=%d", chunk.GetLoc(&dest.Min), chunk.GetSize(&dest.Min))
	}
	
	fmt.Printf("=== FINAL DISTRIBUTION ===\n")
	fmt.Printf("Final split sizes: Max=%d, Mid=%d, Min=%d\n", chunk.GetSize(&dest.Max), chunk.GetSize(&dest.Mid), chunk.GetSize(&dest.Min))
	fmt.Printf("Stack A after split: top=%d, bottom=%d, current_size=%d\n", stack.GetTop(ps.A), stack.GetBottom(ps.A), stack.GetSize(ps.A))
	fmt.Printf("Stack B after split: top=%d, bottom=%d, current_size=%d\n", stack.GetTop(ps.B), stack.GetBottom(ps.B), stack.GetSize(ps.B))
	fmt.Printf("=== CHUNK POSITIONING AFTER SPLIT ===\n")
	fmt.Printf("Chunk positioning after split:\n")
	fmt.Printf("  - MAX chunk: loc=%d, size=%d (should be processed first)\n", chunk.GetLoc(&dest.Max), chunk.GetSize(&dest.Max))
	fmt.Printf("  - MID chunk: loc=%d, size=%d (should be processed second)\n", chunk.GetLoc(&dest.Mid), chunk.GetSize(&dest.Mid))
	fmt.Printf("  - MIN chunk: loc=%d, size=%d (should be processed last)\n", chunk.GetLoc(&dest.Min), chunk.GetSize(&dest.Min))
	fmt.Printf("  - Processing order: MAX(%d) -> MID(%d) -> MIN(%d)\n", chunk.GetLoc(&dest.Max), chunk.GetLoc(&dest.Mid), chunk.GetLoc(&dest.Min))
	fmt.Printf("=== CHUNK_SPLIT END ===\n")
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
