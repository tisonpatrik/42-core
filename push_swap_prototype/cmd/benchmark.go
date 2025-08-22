package main

import (
	"push_swap_prototype/internal/solver"
)

func RunBenchmark(iterations int) bool {
	// Test size 100
	for range iterations {
		numbers := GenerateRandomNumbers(100)
		ops, result := solver.SolvePushSwap(numbers)
		
		if !isSorted(result) {
			return false
		}
		
		if len(ops) > 700 {
			return false
		}
	}
	
	// Test size 500
	for range iterations {
		numbers := GenerateRandomNumbers(500)
		ops, result := solver.SolvePushSwap(numbers)
		
		if !isSorted(result) {
			return false
		}
		
		if len(ops) > 5500 {
			return false
		}
	}
	
	return true
}

func isSorted(arr []int) bool {
	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			return false
		}
	}
	return true
}
