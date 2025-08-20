package benchmark

import (
	"fmt"
	"push_swap_prototype/internal/generator"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/utils"
)

// RunBenchmark runs the push swap benchmark with the specified number of iterations
// Returns true if all iterations succeeded, false if any failed
func RunBenchmark(iterations int) bool {
	// Test size 100 arrays
	if !testArraySize(100, iterations) {
		return false
	}
	
	// Test size 500 arrays
	if !testArraySize(500, iterations) {
		return false
	}
	
	// Display final results
	displayFinalResults()
	return true
}

// testArraySize tests arrays of a specific size and returns success status
func testArraySize(size, iterations int) bool {
	for i := range iterations {
		if !testSingleIteration(size, i+1) {
			return false
		}
	}
	
	return true
}

// testSingleIteration tests a single iteration and returns success status
func testSingleIteration(size, iterationNum int) bool {
	numbers := generator.GenerateRandomNumbers(size)
	ops, finalArray := solver.SolvePushSwap(numbers)
	
	isSorted := utils.IsSorted(finalArray)
	if !isSorted {
		handleIterationFailure(iterationNum, numbers, finalArray)
		return false
	}
	
	// Store successful result for statistics
	storeSuccessfulResult(size, numbers, finalArray, ops)
	return true
}

// handleIterationFailure handles a failed iteration
func handleIterationFailure(iterationNum int, original, final []int) {
	fmt.Printf("❌ Iteration %d failed: Array not sorted properly\n", iterationNum)
	fmt.Printf("   Original: %v\n", original)
	fmt.Printf("   Final:    %v\n", final)
	fmt.Println("\n🛑 Benchmark stopped due to failure!")
}

// storeSuccessfulResult stores a successful benchmark result
func storeSuccessfulResult(size int, original, final []int, ops []string) {
	// Note: In a real implementation, you might want to store these results
	// for statistics. For now, we're just validating success.
	_ = utils.BenchmarkResult{
		Size:           size,
		Operations:     len(ops),
		IsSorted:       true,
		OriginalArray:  original,
		FinalArray:     final,
		OperationList:  ops,
		Failed:         false,
	}
}

// displayFinalResults displays the final benchmark results
func displayFinalResults() {
	fmt.Println("✅ All iterations completed successfully!")
}
