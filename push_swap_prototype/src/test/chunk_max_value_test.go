package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/test/utils"
	"testing"
)

const chunkMaxValueJsonPath = "../../lab/data/chunk_utils/chunk_max_value.json"

// ChunkMaxValueTestCase represents a single test case from the JSON file
type ChunkMaxValueTestCase struct {
	ID         int    `json:"id"`
	Name       string `json:"name"`
	Result     int    `json:"result"`
	ChunkLoc   string `json:"chunk_loc"`
	ChunkSize  int    `json:"chunk_size"`
	InputArray []int  `json:"input_array"`
}

// ChunkMaxValueTestData represents the complete test data structure
type ChunkMaxValueTestData struct {
	Tests []ChunkMaxValueTestCase `json:"tests"`
}

// TestChunkMaxValueWithRealData tests the ChunkMaxValue function using real test data from JSON
func TestChunkMaxValueWithRealData(t *testing.T) {
	// Load real test data using the generic JSON loader
	testData, err := utils.LoadJSONFromFile[ChunkMaxValueTestData](chunkMaxValueJsonPath)
	if err != nil {
		t.Fatalf("Failed to load test data: %v", err)
	}
	
	for _, tc := range testData.Tests {
		t.Run(tc.Name, func(t *testing.T) {
			runChunkMaxValueTest(t, tc)
		})
	}
}

// runChunkMaxValueTest executes a single chunk max value test with proper AAA structure
func runChunkMaxValueTest(t *testing.T, tc ChunkMaxValueTestCase) {
	// Arrange
	chunk, err := utils.CreateChunk(tc.ChunkLoc, tc.ChunkSize)
	if err != nil {
		t.Fatalf("Failed to create chunk: %v", err)
	}
	ps := utils.CreatePushSwapData(tc.InputArray, chunk.Loc)
	
	// Act
	result := solver.ChunkMaxValue(ps, chunk)
	
	// Assert
	assertChunkMaxValueResult(t, tc, result)
}

// assertChunkMaxValueResult asserts that the result matches the expected value
func assertChunkMaxValueResult(t *testing.T, tc ChunkMaxValueTestCase, result int) {
	if result != tc.Result {
		t.Errorf("ChunkMaxValue(ps, chunk) = %d, want %d", result, tc.Result)
	}
}
