package test

import (
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
	"testing"
)

// TestChunkToTheTopTOP_A_RealLife tests chunkToTheTop with TOP_A location from real-life scenario
// Log reference: chunk.Loc=0 (TOP_A), chunk.Size=59 - chunkToTheTop does NOT change the location
func TestChunkToTheTopTOP_A_RealLife(t *testing.T) {
	// Arrange - EXACT data from real-life scenario
	ps := stack.NewPushSwapDataWithCapacity(100)
	
	// Fill stack A with 59 elements (like in the failing test)
	for i := 100; i >= 42; i-- {
		ps.A.Push(i)
	}
	
	chunk := &stack.Chunk{
		Loc:  stack.TOP_A,  // EXACT from logs: chunk.Loc=0
		Size: 59,           // EXACT from logs: chunk.Size=59
	}
	
	// Act
	solver.ChunkToTheTop(ps, chunk)
	
	// Assert - chunkToTheTop should NOT change TOP_A location
	expectedLoc := stack.TOP_A
	if chunk.Loc != expectedLoc {
		t.Errorf("chunkToTheTop changed TOP_A location from %v to %v, but should remain %v", 
			stack.TOP_A, chunk.Loc, expectedLoc)
	}
	
	// Size should remain unchanged
	expectedSize := 59
	if chunk.Size != expectedSize {
		t.Errorf("chunkToTheTop changed size from %d to %d, but should remain %d", 
			59, chunk.Size, expectedSize)
	}
	
	t.Logf("chunkToTheTop with TOP_A location works correctly - location unchanged (from real-life scenario)")
}

// TestChunkToTheTopBOTTOM_A_RealLife tests chunkToTheTop with BOTTOM_A location from real-life scenario
// Log reference: chunk.Loc=1 (BOTTOM_A) - chunkToTheTop should change to TOP_A
func TestChunkToTheTopBOTTOM_A_RealLife(t *testing.T) {
	// Arrange - EXACT data from real-life scenario
	ps := stack.NewPushSwapDataWithCapacity(100)
	
	// Fill stack A with 59 elements (like in the failing test)
	for i := 100; i >= 42; i-- {
		ps.A.Push(i)
	}
	
	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_A,  // EXACT from logs: chunk.Loc=1
		Size: 59,              // EXACT from logs: chunk.Size=59
	}
	
	// Act
	solver.ChunkToTheTop(ps, chunk)
	
	// Assert - chunkToTheTop should change BOTTOM_A to TOP_A when size matches
	expectedLoc := stack.TOP_A
	if chunk.Loc != expectedLoc {
		t.Errorf("chunkToTheTop should change BOTTOM_A to TOP_A, but got %v", chunk.Loc)
	}
	
	// Size should remain unchanged
	expectedSize := 59
	if chunk.Size != expectedSize {
		t.Errorf("chunkToTheTop changed size from %d to %d, but should remain %d", 
			59, chunk.Size, expectedSize)
	}
	
	t.Logf("chunkToTheTop with BOTTOM_A location works correctly - changed to TOP_A (from real-life scenario)")
}

// TestChunkToTheTopBOTTOM_B_RealLife tests chunkToTheTop with BOTTOM_B location from real-life scenario
// Log reference: chunk.Loc=3 (BOTTOM_B) - chunkToTheTop should change to TOP_B
func TestChunkToTheTopBOTTOM_B_RealLife(t *testing.T) {
	// Arrange - EXACT data from real-life scenario
	ps := stack.NewPushSwapDataWithCapacity(100)
	
	// Fill stack B with 59 elements (like in the failing test)
	for i := 100; i >= 42; i-- {
		ps.B.Push(i)
	}
	
	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_B,  // EXACT from logs: chunk.Loc=3
		Size: 59,              // EXACT from logs: chunk.Size=59
	}
	
	// Act
	solver.ChunkToTheTop(ps, chunk)
	
	// Assert - chunkToTheTop should change BOTTOM_B to TOP_B when size matches
	expectedLoc := stack.TOP_B
	if chunk.Loc != expectedLoc {
		t.Errorf("chunkToTheTop should change BOTTOM_B to TOP_B, but got %v", chunk.Loc)
	}
	
	// Size should remain unchanged
	expectedSize := 59
	if chunk.Size != expectedSize {
		t.Errorf("chunkToTheTop changed size from %d to %d, but should remain %d", 
			59, chunk.Size, expectedSize)
	}
	
	t.Logf("chunkToTheTop with BOTTOM_B location works correctly - changed to TOP_B (from real-life scenario)")
}

// TestChunkToTheTopTOP_B_RealLife tests chunkToTheTop with TOP_B location from real-life scenario
// Log reference: chunk.Loc=2 (TOP_B) - chunkToTheTop should NOT change the location
func TestChunkToTheTopTOP_B_RealLife(t *testing.T) {
	// Arrange - EXACT data from real-life scenario
	ps := stack.NewPushSwapDataWithCapacity(100)
	
	// Fill stack B with 59 elements (like in the failing test)
	for i := 100; i >= 42; i-- {
		ps.B.Push(i)
	}
	
	chunk := &stack.Chunk{
		Loc:  stack.TOP_B,  // EXACT from logs: chunk.Loc=2
		Size: 59,           // EXACT from logs: chunk.Size=59
	}
	
	// Act
	solver.ChunkToTheTop(ps, chunk)
	
	// Assert - chunkToTheTop should NOT change TOP_B location
	expectedLoc := stack.TOP_B
	if chunk.Loc != expectedLoc {
		t.Errorf("chunkToTheTop changed TOP_B location from %v to %v, but should remain %v", 
			stack.TOP_B, chunk.Loc, expectedLoc)
	}
	
	// Size should remain unchanged
	expectedSize := 59
	if chunk.Size != expectedSize {
		t.Errorf("chunkToTheTop changed size from %d to %d, but should remain %d", 
			59, chunk.Size, expectedSize)
	}
	
	t.Logf("chunkToTheTop with TOP_B location works correctly - location unchanged (from real-life scenario)")
}

// TestChunkToTheTopSizeMismatch tests chunkToTheTop when chunk size doesn't match stack size
// Real-life scenario: chunk size should NOT change location when sizes don't match
func TestChunkToTheTopSizeMismatch(t *testing.T) {
	// Arrange - EXACT data from real-life scenario
	ps := stack.NewPushSwapDataWithCapacity(100)
	
	// Fill stack A with 59 elements (like in the failing test)
	for i := 100; i >= 42; i-- {
		ps.A.Push(i)
	}
	
	chunk := &stack.Chunk{
		Loc:  stack.BOTTOM_A,  // Should change to TOP_A only if size matches
		Size: 30,              // Different size than stack (59)
	}
	
	// Act
	solver.ChunkToTheTop(ps, chunk)
	
	// Assert - chunkToTheTop should NOT change location when sizes don't match
	expectedLoc := stack.BOTTOM_A
	if chunk.Loc != expectedLoc {
		t.Errorf("chunkToTheTop changed BOTTOM_A to %v when sizes don't match, but should remain %v", 
			chunk.Loc, expectedLoc)
	}
	
	// Size should remain unchanged
	expectedSize := 30
	if chunk.Size != expectedSize {
		t.Errorf("chunkToTheTop changed size from %d to %d, but should remain %d", 
			30, chunk.Size, expectedSize)
	}
	
	t.Logf("chunkToTheTop with size mismatch works correctly - location unchanged (from real-life scenario)")
}
