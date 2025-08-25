package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestChunkValueTOP_A_Offset1 tests chunk_value for TOP_A with offset 1
// Log reference: Line 19 - Stack A elements: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestChunkValueTOP_A_Offset1(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 100, // EXACT from log line 28
	}

	// Act
	result := solver.ChunkValue(ps, chunk, 1)

	// Assert - EXACT first element from log line 19
	expected := 53
	if result != expected {
		t.Errorf("ChunkValue(ps, chunk, 1) = %d, want %d (from log line 19)", result, expected)
	}
}

// TestChunkValueTOP_A_Offset2 tests chunk_value for TOP_A with offset 2
// Log reference: Line 19 - Stack A elements: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestChunkValueTOP_A_Offset2(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 100, // EXACT from log line 28
	}

	// Act
	result := solver.ChunkValue(ps, chunk, 2)

	// Assert - EXACT second element from log line 19
	expected := 12
	if result != expected {
		t.Errorf("ChunkValue(ps, chunk, 2) = %d, want %d (from log line 19)", result, expected)
	}
}

// TestChunkValueTOP_A_Offset3 tests chunk_value for TOP_A with offset 3
// Log reference: Line 19 - Stack A elements: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestChunkValueTOP_A_Offset3(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,
		Size: 100, // EXACT from log line 28
	}

	// Act
	result := solver.ChunkValue(ps, chunk, 3)

	// Assert - EXACT third element from log line 19
	expected := 18
	if result != expected {
		t.Errorf("ChunkValue(ps, chunk, 3) = %d, want %d (from log line 19)", result, expected)
	}
}

// TestChunkValueBOTTOM_A_Offset1 tests chunk_value for BOTTOM_A with offset 1
// Log reference: Line 19 - Stack A elements: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestChunkValueBOTTOM_A_Offset1(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_A,
		Size: 100, // EXACT from log line 28
	}

	// Act
	result := solver.ChunkValue(ps, chunk, 1)

	// Assert - EXACT last element from log line 19
	expected := 65
	if result != expected {
		t.Errorf("ChunkValue(ps, chunk, 1) = %d, want %d (from log line 19)", result, expected)
	}
}

// TestChunkValueBOTTOM_A_Offset2 tests chunk_value for BOTTOM_A with offset 2
// Log reference: Line 19 - Stack A elements: [53 12 18 68 36 72 98 54 61 43 89 34 5 27 57 15 79 91 51 26 76 88 42 55 10 93 71 58 74 8 46 90 31 48 59 1 85 49 97 64 37 29 70 3 22 19 80 47 75 40 24 96 86 11 52 32 4 21 25 33 9 2 99 95 100 83 45 28 41 17 56 44 20 13 67 35 69 77 78 92 73 62 38 63 81 16 50 94 87 66 30 84 60 23 82 39 6 7 14 65]
func TestChunkValueBOTTOM_A_Offset2(t *testing.T) {
	// Arrange - EXACT data from log line 19
	inputArray := []int{53, 12, 18, 68, 36, 72, 98, 54, 61, 43, 89, 34, 5, 27, 57, 15, 79, 91, 51, 26, 76, 88, 42, 55, 10, 93, 71, 58, 74, 8, 46, 90, 31, 48, 59, 1, 85, 49, 97, 64, 37, 29, 70, 3, 22, 19, 80, 47, 75, 40, 24, 96, 86, 11, 52, 32, 4, 21, 25, 33, 9, 2, 99, 95, 100, 83, 45, 28, 41, 17, 56, 44, 20, 13, 67, 35, 69, 77, 78, 92, 73, 62, 38, 63, 81, 16, 50, 94, 87, 66, 30, 84, 60, 23, 82, 39, 6, 7, 14, 65}

	ps := stack.NewPushSwapDataWithCapacity(100)
	stack.InitializeFromSlice(ps, inputArray)

	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_A,
		Size: 100, // EXACT from log line 28
	}

	// Act
	result := solver.ChunkValue(ps, chunk, 2)

	// Assert - EXACT second to last element from log line 19
	expected := 14
	if result != expected {
		t.Errorf("ChunkValue(ps, chunk, 2) = %d, want %d (from log line 19)", result, expected)
	}
}
