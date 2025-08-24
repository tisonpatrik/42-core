package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/test/utils"
	"testing"
)

const jsonPath = "../../lab/data/chunk_utils/chunk_value.json"

// ChunkValueTestCase represents a single test case from the JSON file
type ChunkValueTestCase struct {
	ID         int    `json:"id"`
	Name       string `json:"name"`
	Result     int    `json:"result"`
	ChunkLoc   string `json:"chunk_loc"`
	ChunkSize  int    `json:"chunk_size"`
	Offset     int    `json:"offset"`
	InputArray []int  `json:"input_array"`
}

// ChunkValueTestData represents the complete test data structure
type ChunkValueTestData struct {
	Tests []ChunkValueTestCase `json:"tests"`
}

// TestChunkValueWithRealData tests the ChunkValue function using real test data from JSON
func TestChunkValueWithRealData(t *testing.T) {
	// Load real test data using the generic JSON loader
	testData, err := utils.LoadJSONFromFile[ChunkValueTestData](jsonPath)
	if err != nil {
		t.Fatalf("Failed to load test data: %v", err)
	}
	
	for _, tc := range testData.Tests {
		t.Run(tc.Name, func(t *testing.T) {
			runChunkValueTest(t, tc)
		})
	}
}

// runChunkValueTest executes a single chunk value test with proper AAA structure
func runChunkValueTest(t *testing.T, tc ChunkValueTestCase) {
	// Arrange
	chunk, err := utils.CreateChunk(tc.ChunkLoc, tc.ChunkSize)
	if err != nil {
		t.Fatalf("Failed to create chunk: %v", err)
	}
	ps := utils.CreatePushSwapData(tc.InputArray, chunk.Loc)
	
	// Act
	result := solver.ChunkValue(ps, chunk, tc.Offset)
	
	// Assert
	assertChunkValueResult(t, tc, result)
}

// assertChunkValueResult asserts that the result matches the expected value
func assertChunkValueResult(t *testing.T, tc ChunkValueTestCase, result int) {
	if result != tc.Result {
		t.Errorf("ChunkValue(ps, chunk, %d) = %d, want %d", tc.Offset, result, tc.Result)
	}
}
