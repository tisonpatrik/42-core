package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/benchmark"
	"push_swap_prototype/internal/solver"
)

func main() {
	// First test with simple arrays to debug
	fmt.Println("=== DEBUGGING SOLVER ===")
	
	// Test with a simple array first
	testArray := []int{3, 1, 2}
	fmt.Printf("Testing with array: %v\n", testArray)
	
	ops, result := solver.SolvePushSwap(testArray)
	fmt.Printf("Operations: %v\n", ops)
	fmt.Printf("Result: %v\n", result)
	
	// Test with a slightly larger array
	testArray2 := []int{5, 2, 3, 1, 4}
	fmt.Printf("\nTesting with array: %v\n", testArray2)
	
	ops2, result2 := solver.SolvePushSwap(testArray2)
	fmt.Printf("Operations: %v\n", ops2)
	fmt.Printf("Result: %v\n", result2)
	
	// Test with a failing array from the benchmark
	testArray3 := []int{28, 91, 64, 50, 62, 87, 88, 47, 74, 15, 25, 70, 89, 20, 66, 22, 57, 5, 72, 95, 86, 41, 39, 54, 82, 63, 92, 53, 19, 46, 51, 12, 0, 6, 24, 36, 2, 33, 1, 68, 80, 26, 85, 90, 10, 16, 84, 37, 29, 4, 69, 67, 61, 30, 49, 45, 65, 34, 7, 98, 38, 48, 21, 79, 75, 60, 3, 93, 27, 52, 17, 99, 97, 73, 23, 32, 43, 8, 56, 44, 77, 76, 9, 94, 14, 35, 59, 31, 78, 81, 58, 55, 71, 11, 40, 83, 18, 96, 13, 42}
	fmt.Printf("\nTesting with failing array (first 10 elements): %v\n", testArray3[:10])
	
	ops3, result3 := solver.SolvePushSwap(testArray3)
	fmt.Printf("Operations count: %d\n", len(ops3))
	fmt.Printf("Result (first 20 elements): %v\n", result3[:20])
	
	// Check if it's sorted
	isSorted := true
	for i := 1; i < len(result3); i++ {
		if result3[i] < result3[i-1] {
			isSorted = false
			fmt.Printf("❌ Not sorted at position %d: %d > %d\n", i, result3[i-1], result3[i])
			break
		}
	}
	if isSorted {
		fmt.Printf("✅ Array is sorted!\n")
	} else {
		fmt.Printf("❌ Array is NOT sorted!\n")
	}
	
	fmt.Println("\n=== RUNNING BENCHMARK ===")
	
	// Run the benchmark
	success := benchmark.RunBenchmark(1)
	
	if !success {
		os.Exit(1)
	}
}
