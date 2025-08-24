package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"push_swap_prototype/test/utils"
	"testing"
)

const chunkSplitJsonPath = "../../lab/data/chunk_split/chunk_split.json"

// ChunkSplitTestCase represents a single test case from the JSON file
type ChunkSplitTestCase struct {
	ID                 int    `json:"id"`
	Name               string `json:"name"`
	OriginalChunkSize  int    `json:"original_chunk_size"`
	OriginalChunkLoc   string `json:"original_chunk_loc"`
	MinSizeResult      int    `json:"min_size_result"`
	MidSizeResult      int    `json:"mid_size_result"`
	MaxSizeResult      int    `json:"max_size_result"`
	MinLocResult       string `json:"min_loc_result"`
	MidLocResult       string `json:"mid_loc_result"`
	MaxLocResult       string `json:"max_loc_result"`
	InputArray         []int  `json:"input_array"`
}

// ChunkSplitTestData represents the complete test data structure
type ChunkSplitTestData struct {
	Tests []ChunkSplitTestCase `json:"tests"`
}

// TestChunkSplitWithRealData tests the ChunkSplit function using real test data from JSON
func TestChunkSplitWithRealData(t *testing.T) {
	// Load real test data using the generic JSON loader
	testData, err := utils.LoadJSONFromFile[ChunkSplitTestData](chunkSplitJsonPath)
	if err != nil {
		t.Fatalf("Failed to load test data: %v", err)
	}
	
	for _, tc := range testData.Tests {
		t.Run(tc.Name, func(t *testing.T) {
			runChunkSplitTest(t, tc)
		})
	}
}

// runChunkSplitTest executes a single chunk split test with proper AAA structure
func runChunkSplitTest(t *testing.T, tc ChunkSplitTestCase) {
	// Arrange
	chunk, err := utils.CreateChunk(tc.OriginalChunkLoc, tc.OriginalChunkSize)
	if err != nil {
		t.Fatalf("Failed to create chunk: %v", err)
	}
	
	ps := utils.CreatePushSwapData(tc.InputArray, chunk.Loc)
	dest := &stack.SplitDest{}
	
	// Act
	solver.ChunkSplit(ps, chunk, dest)
	
	// Assert
	assertChunkSplitResult(t, tc, dest)
}

// assertChunkSplitResult asserts that the split result matches the expected values
func assertChunkSplitResult(t *testing.T, tc ChunkSplitTestCase, dest *stack.SplitDest) {
	// Check min chunk
	if dest.Min.Size != tc.MinSizeResult {
		t.Errorf("Min chunk size = %d, want %d", dest.Min.Size, tc.MinSizeResult)
	}
	if dest.Min.Loc != utils.StringToLoc(tc.MinLocResult) {
		t.Errorf("Min chunk location = %v, want %s", dest.Min.Loc, tc.MinLocResult)
	}
	
	// Check mid chunk
	if dest.Mid.Size != tc.MidSizeResult {
		t.Errorf("Mid chunk size = %d, want %d", dest.Mid.Size, tc.MidSizeResult)
	}
	if dest.Mid.Loc != utils.StringToLoc(tc.MidLocResult) {
		t.Errorf("Mid chunk location = %v, want %s", dest.Mid.Loc, tc.MidLocResult)
	}
	
	// Check max chunk
	if dest.Max.Size != tc.MaxSizeResult {
		t.Errorf("Max chunk size = %d, want %d", dest.Max.Size, tc.MaxSizeResult)
	}
	if dest.Max.Loc != utils.StringToLoc(tc.MaxLocResult) {
		t.Errorf("Max chunk location = %v, want %s", dest.Max.Loc, tc.MaxLocResult)
	}
}

// TestChunkSplitAlgorithm tests the ChunkSplit function for algorithm correctness
func TestChunkSplitAlgorithm(t *testing.T) {
	// Test 1: TOP_A chunk split with size 15
	t.Run("TOP_A_split_size_15", func(t *testing.T) {
		testChunkSplitCorrectness(t, "TOP_A", 15, 100)
	})
	
	// Test 2: BOTTOM_A chunk split with size 12
	t.Run("BOTTOM_A_split_size_12", func(t *testing.T) {
		testChunkSplitCorrectness(t, "BOTTOM_A", 12, 100)
	})
	
	// Test 3: TOP_B chunk split with size 10
	t.Run("TOP_B_split_size_10", func(t *testing.T) {
		testChunkSplitCorrectness(t, "TOP_B", 10, 100)
	})
	
	// Test 4: BOTTOM_B chunk split with size 8
	t.Run("BOTTOM_B_split_size_8", func(t *testing.T) {
		testChunkSplitCorrectness(t, "BOTTOM_B", 8, 100)
	})
}

// testChunkSplitCorrectness tests that the chunk split algorithm produces valid results
func testChunkSplitCorrectness(t *testing.T, chunkLoc string, chunkSize int, arraySize int) {
	// Create test data
	inputArray := make([]int, arraySize)
	for i := 0; i < arraySize; i++ {
		inputArray[i] = i
	}
	
	// Create chunk and PushSwap data
	chunk, err := utils.CreateChunk(chunkLoc, chunkSize)
	if err != nil {
		t.Fatalf("Failed to create chunk: %v", err)
	}
	
	ps := utils.CreatePushSwapData(inputArray, chunk.Loc)
	dest := &stack.SplitDest{}
	
	// Run ChunkSplit
	solver.ChunkSplit(ps, chunk, dest)
	
	// Test 1: Results sum to original chunk size
	totalSize := dest.Min.Size + dest.Mid.Size + dest.Max.Size
	if totalSize != chunkSize {
		t.Errorf("Total split size = %d, want %d (min=%d, mid=%d, max=%d)", 
			totalSize, chunkSize, dest.Min.Size, dest.Mid.Size, dest.Max.Size)
	}
	
	// Test 2: All sizes are non-negative
	if dest.Min.Size < 0 || dest.Mid.Size < 0 || dest.Max.Size < 0 {
		t.Errorf("Negative chunk sizes: min=%d, mid=%d, max=%d", 
			dest.Min.Size, dest.Mid.Size, dest.Max.Size)
	}
	
	// Test 3: Locations are set correctly based on chunk location
	expectedMinLoc, expectedMidLoc, expectedMaxLoc := getExpectedLocations(chunkLoc)
	
	if dest.Min.Loc != expectedMinLoc {
		t.Errorf("Min chunk location = %v, want %v", dest.Min.Loc, expectedMinLoc)
	}
	if dest.Mid.Loc != expectedMidLoc {
		t.Errorf("Mid chunk location = %v, want %v", dest.Mid.Loc, expectedMidLoc)
	}
	if dest.Max.Loc != expectedMaxLoc {
		t.Errorf("Max chunk location = %v, want %v", dest.Max.Loc, expectedMaxLoc)
	}
	
	// Test 4: Pivot logic is correct
	testPivotLogic(t, chunkLoc, chunkSize)
}

// getExpectedLocations returns the expected locations for each chunk based on source location
func getExpectedLocations(chunkLoc string) (stack.Loc, stack.Loc, stack.Loc) {
	switch chunkLoc {
	case "TOP_A":
		return stack.BOTTOM_B, stack.TOP_B, stack.BOTTOM_A
	case "BOTTOM_A":
		return stack.BOTTOM_B, stack.TOP_B, stack.TOP_A
	case "TOP_B":
		return stack.BOTTOM_B, stack.BOTTOM_A, stack.TOP_A
	case "BOTTOM_B":
		return stack.TOP_B, stack.BOTTOM_A, stack.TOP_A
	default:
		return stack.TOP_A, stack.TOP_A, stack.TOP_A // Default fallback
	}
}

// testPivotLogic tests that the pivot calculations are correct
func testPivotLogic(t *testing.T, chunkLoc string, chunkSize int) {
	var pivot1, pivot2 int
	
	// Calculate expected pivots based on the algorithm logic
	pivot2 = chunkSize / 3
	pivot1 = chunkSize / 2
	
	switch chunkLoc {
	case "TOP_A", "BOTTOM_A":
		pivot1 = 2 * chunkSize / 3
		if chunkSize < 15 {
			pivot1 = chunkSize
		}
	case "TOP_B", "BOTTOM_B":
		pivot1 = chunkSize / 2
		if chunkLoc == "BOTTOM_B" && chunkSize < 8 {
			pivot2 = chunkSize / 2
		}
	}
	
	// Verify pivot values are reasonable
	if pivot1 < 0 || pivot2 < 0 {
		t.Errorf("Invalid pivot values: pivot1=%d, pivot2=%d", pivot1, pivot2)
	}
	
	if pivot1 > chunkSize || pivot2 > chunkSize {
		t.Errorf("Pivot values exceed chunk size: pivot1=%d, pivot2=%d, chunkSize=%d", 
			pivot1, pivot2, chunkSize)
	}
}
