package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestChunkMaxValueTOP_A_FullChunk tests chunk_max_value for TOP_A with full 100-element chunk
// Log reference: Line 138 - "Max value in chunk: 100"
func TestChunkMaxValueTOP_A_FullChunk(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 100, // EXACT from log line 28
	}

	// Act
	result := solver.ChunkMaxValue(ps, chunk)

	// Assert - EXACT from log line 138
	expected := 100
	if result != expected {
		t.Errorf("ChunkMaxValue(ps, chunk) = %d, want %d (from log line 138)", result, expected)
	}
}

// TestChunkMaxValueTOP_A_First10 tests chunk_max_value for TOP_A with first 10 elements
// Log reference: Line 19 - Stack A elements: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestChunkMaxValueTOP_A_First10(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 10, // Test smaller chunk
	}

	// Act
	result := solver.ChunkMaxValue(ps, chunk)

	// Assert - Max of first 10: [53 12 18 68 36 72 98 54 61 43]
	expected := 98
	if result != expected {
		t.Errorf("ChunkMaxValue(ps, chunk) = %d, want %d (from log line 19)", result, expected)
	}
}

// TestChunkMaxValueBOTTOM_B_ChunkSize6 tests chunk_max_value for BOTTOM_B with chunk size 6
// Log reference: Line 1674 - "Max value in chunk: 84" and Line 1670 - Stack B elements: [65 39 60 66 50 63 38 62 35 67 44 56 41 45 52 40 47 37 64 49 59 48 46 58 55 42 51 57 43 61 54 36 53 12 18 34 5 27 15 26 10 8 31 1 29 3 22 19 24 11 32 4 21 25 33 9 2 28 17 20 13 16 30 23 6 7 14 68 72 76 71 74 70 75 69 77 78 73 82 84 81 83 80 79]
func TestChunkMaxValueBOTTOM_B_ChunkSize6(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	// For BOTTOM_B test, we need to simulate the exact Stack B state from log line 1670
	stackBData := []int{65, 39, 60, 66, 50, 63, 38, 62, 35, 67, 44, 56, 41, 45, 52, 40, 47, 37, 64, 49, 59, 48, 46, 58, 55, 42, 51, 57, 43, 61, 54, 36, 53, 12, 18, 34, 5, 27, 15, 26, 10, 8, 31, 1, 29, 3, 22, 19, 24, 11, 32, 4, 21, 25, 33, 9, 2, 28, 17, 20, 13, 16, 30, 23, 6, 7, 14, 68, 72, 76, 71, 74, 70, 75, 69, 77, 78, 73, 82, 84, 81, 83, 80, 79}
	ps.B.FillFromSlice(stackBData)

	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_B,
		Size: 6, // EXACT from log line 1672: "Splitting chunk: loc=3, size=6"
	}

	// Act
	result := solver.ChunkMaxValue(ps, chunk)

	// Assert - EXACT from log line 1674: "Max value in chunk: 84"
	expected := 84
	if result != expected {
		t.Errorf("ChunkMaxValue(ps, chunk) = %d, want %d (from log line 1674)", result, expected)
	}
}
