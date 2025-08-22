package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/solver"
	"strconv"
)

func main() {
	if len(os.Args) < 2 {
		os.Exit(1)
	}

	// Parse command line arguments to integers
	var numbers []int
	for i := 1; i < len(os.Args); i++ {
		num, err := strconv.Atoi(os.Args[i])
		if err != nil {
			fmt.Printf("Error: '%s' is not a valid integer\n", os.Args[i])
			os.Exit(1)
		}
		numbers = append(numbers, num)
	}

	fmt.Printf("=== MAIN START ===\n")
	fmt.Printf("Testing with array: %v\n", numbers)
	fmt.Printf("Array size: %d\n", len(numbers))
	fmt.Printf("=== MAIN END ===\n")

	// Solve the push swap problem
	fmt.Printf("=== SOLVING START ===\n")
	ops, result := solver.SolvePushSwap(numbers)
	fmt.Printf("=== SOLVING END ===\n")
	
	fmt.Printf("=== RESULTS ===\n")
	fmt.Printf("Operations count: %d\n", len(ops))
	fmt.Printf("Result: %v\n", result)
	
	// Check if it's sorted
	isSorted := true
	for i := 1; i < len(result); i++ {
		if result[i] < result[i-1] {
			isSorted = false
			fmt.Printf("❌ Not sorted at position %d: %d > %d\n", i, result[i-1], result[i])
			break
		}
	}
	if isSorted {
		fmt.Printf("✅ Array is sorted!\n")
	} else {
		fmt.Printf("❌ Array is NOT sorted!\n")
		os.Exit(1)
	}
	fmt.Printf("=== RESULTS END ===\n")
}
