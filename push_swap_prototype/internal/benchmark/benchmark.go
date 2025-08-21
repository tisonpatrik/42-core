package benchmark

import (
	"fmt"
	"math/rand"
	"push_swap_prototype/internal/generator"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/utils"
	"sort"
	"strings"
	"time"
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
	startTime := time.Now()
	
	// Seed the random number generator with current time
	rand.Seed(startTime.UnixNano())
	
	fmt.Printf("Starting Push Swap Benchmark with %d iterations per size\n", iterations)
	fmt.Printf("Testing sizes: 100 and 500\n")
	fmt.Printf("Started at: %s\n\n", startTime.Format("15:04:05"))
	
	// Test size 100
	separator50 := strings.Repeat("=", 50)
	fmt.Printf("%s\n", separator50)
	fmt.Println("TESTING SIZE 100")
	fmt.Printf("%s\n", separator50)
	size100Result := testArraySize(100, iterations)
	if size100Result == nil {
		return false
	}
	
	// Test size 500
	fmt.Printf("\n%s\n", separator50)
	fmt.Println("TESTING SIZE 500")
	fmt.Printf("%s\n", separator50)
	size500Result := testArraySize(500, iterations)
	if size500Result == nil {
		return false
	}
	
	// Display final results
	displayFinalResults(size100Result, size500Result)
	return true
}

// testArraySize tests arrays of a specific size and returns results
func testArraySize(size, iterations int) *SizeResult {
	fmt.Printf("Running %d iterations...\n", iterations)
	
	result := &SizeResult{
		Size:         size,
		Operations:   make([]int, 0, iterations),
		MinOps:       -1,
		MaxOps:       0,
		TotalCount:   iterations,
	}
	
	for i := 0; i < iterations; i++ {
		// Show progress every 10 iterations
		if i > 0 && i%10 == 0 {
			fmt.Printf("   Progress: %d/%d\n", i, iterations)
		}
		
		numbers := generator.GenerateRandomNumbers(size)
		ops, finalArray := solver.SolvePushSwap(numbers)
		
		isSorted := utils.IsSorted(finalArray)
		if !isSorted {
			fmt.Printf("❌ Iteration %d failed: Array not sorted properly\n", i+1)
			fmt.Printf("   Original: %v\n", numbers)
			fmt.Printf("   Final:    %v\n", finalArray)
			return nil
		}
		
		opCount := len(ops)
		result.Operations = append(result.Operations, opCount)
		result.SuccessCount++
		
		// Debug: Show first few iterations with details
		if i < 3 {
			fmt.Printf("   Iteration %d: %d operations\n", i+1, opCount)
			if i == 0 {
				fmt.Printf("      Sample operations: %v\n", ops[:min(5, len(ops))])
				fmt.Printf("      Original array: %v\n", numbers[:min(5, len(numbers))])
				fmt.Printf("      Final array: %v\n", finalArray[:min(5, len(finalArray))])
			}
		}
		
		// Update min/max
		if result.MinOps == -1 || opCount < result.MinOps {
			result.MinOps = opCount
		}
		if opCount > result.MaxOps {
			result.MaxOps = opCount
		}
	}
	
	// Calculate statistics
	result.calculateStats()
	
	// Display results for this size
	displaySizeResults(result)
	
	return result
}

// min returns the smaller of two integers
func min(a, b int) int {
	if a < b {
		return a
	}
	return b
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

// displaySizeResults displays results for a specific size
func displaySizeResults(result *SizeResult) {
	fmt.Printf("\nRESULTS FOR SIZE %d:\n", result.Size)
	fmt.Printf("   Successful runs: %d/%d\n", result.SuccessCount, result.TotalCount)
	fmt.Printf("   Min operations: %d\n", result.MinOps)
	fmt.Printf("   Max operations: %d\n", result.MaxOps)
	fmt.Printf("   Average operations: %.1f\n", result.AvgOps)
	fmt.Printf("   Median operations: %d\n", result.MedianOps)
	
	// Check validation
	maxAllowed := MaxOps100
	if result.Size == 500 {
		maxAllowed = MaxOps500
	}
	
	if result.MaxOps < maxAllowed {
		fmt.Printf("   ✅ VALIDATION: PASSED (max %d < %d)\n", result.MaxOps, maxAllowed)
	} else {
		fmt.Printf("   ❌ VALIDATION: FAILED (max %d >= %d)\n", result.MaxOps, maxAllowed)
	}
	
	// Show operation distribution if we have results
	if len(result.Operations) > 0 {
		fmt.Printf("   Operation counts: %v\n", result.Operations)
	}
}

// displayFinalResults displays the final benchmark results
func displayFinalResults(size100, size500 *SizeResult) {
	separator60 := strings.Repeat("=", 60)
	fmt.Printf("\n%s\n", separator60)
	fmt.Println("FINAL BENCHMARK RESULTS")
	fmt.Printf("%s\n", separator60)
	
	// Overall summary
	fmt.Printf("Total successful runs: %d\n", size100.SuccessCount+size500.SuccessCount)
	
	// Size 100 summary
	fmt.Printf("\nSIZE 100 SUMMARY:\n")
	fmt.Printf("   Max operations: %d (target: < %d)\n", size100.MaxOps, MaxOps100)
	if size100.MaxOps < MaxOps100 {
		fmt.Printf("   ✅ 100%% validation: ACHIEVED\n")
	} else {
		fmt.Printf("   ❌ 100%% validation: NOT ACHIEVED\n")
	}
	
	// Size 500 summary
	fmt.Printf("\nSIZE 500 SUMMARY:\n")
	fmt.Printf("   Max operations: %d (target: < %d)\n", size500.MaxOps, MaxOps500)
	if size500.MaxOps < MaxOps500 {
		fmt.Printf("   ✅ 100%% validation: ACHIEVED\n")
	} else {
		fmt.Printf("   ❌ 100%% validation: NOT ACHIEVED\n")
	}
	
	// Overall grade
	if size100.MaxOps < MaxOps100 && size500.MaxOps < MaxOps500 {
		fmt.Printf("\n🏆 OVERALL GRADE: 100%% (Excellent! Eligible for bonuses)\n")
	} else if size100.MaxOps < MaxOps100 || size500.MaxOps < MaxOps500 {
		fmt.Printf("\n🎯 OVERALL GRADE: PARTIAL (Some targets met)\n")
	} else {
		fmt.Printf("\n💥 OVERALL GRADE: FAIL (No targets met)\n")
	}
	
	fmt.Printf("%s\n", separator60)
}
