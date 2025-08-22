package benchmark

import (
	"push_swap_prototype/internal/generator"
	"push_swap_prototype/internal/solver"
	"sort"
)

// Validation thresholds
const (
	MaxOps100 = 700  // 100% validation for size 100
	MaxOps500 = 5500 // 100% validation for size 500
)

// SizeResult stores results for a specific size
type SizeResult struct {
	Size           int
	Operations     []int
	MinOps         int
	MaxOps         int
	AvgOps         float64
	MedianOps      int
	SuccessCount   int
	TotalCount     int
}

// RunBenchmark runs the push swap benchmark with the specified number of iterations
func RunBenchmark(iterations int) bool {
	
	// Test size 100
	size100Result := testArraySize(100, iterations)
	if size100Result == nil {
		return false
	}
	
	// Test size 500
	size500Result := testArraySize(500, iterations)
	if size500Result == nil {
		return false
	}
	
	return true
}

// testArraySize tests arrays of a specific size and returns results
func testArraySize(size, iterations int) *SizeResult {
	result := &SizeResult{
		Size:         size,
		Operations:   make([]int, 0, iterations),
		MinOps:       -1,
		MaxOps:       0,
		TotalCount:   iterations,
	}

	for range iterations {
		numbers := generator.GenerateRandomNumbers(size)
		ops, finalArray := solver.SolvePushSwap(numbers)

		isSorted := isSorted(finalArray)
		if !isSorted {
			return nil
		}
		
		opCount := len(ops)
		result.Operations = append(result.Operations, opCount)
		result.SuccessCount++
		
		// Update min/max
		if result.MinOps == -1 || opCount < result.MinOps {
			result.MinOps = opCount
		}
		if opCount > result.MaxOps {
			result.MaxOps = opCount
		}
	}
	
	result.calculateStats()
	return result
}

// isSorted checks if an array of integers is sorted in ascending order
func isSorted(arr []int) bool {
	if len(arr) <= 1 {
		return true
	}
	
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			return false
		}
	}
	return true
}

// calculateStats calculates statistics for the size result
func (sr *SizeResult) calculateStats() {
	if len(sr.Operations) == 0 {
		return
	}
	
	// Calculate average
	sum := 0
	for _, ops := range sr.Operations {
		sum += ops
	}
	sr.AvgOps = float64(sum) / float64(len(sr.Operations))
	
	// Calculate median
	sortedOps := make([]int, len(sr.Operations))
	copy(sortedOps, sr.Operations)
	sort.Ints(sortedOps)
	sr.MedianOps = sortedOps[len(sortedOps)/2]
}
