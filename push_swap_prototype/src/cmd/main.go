package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/solver"
	"strconv"
)

func main() {
	args := os.Args[1:]
	if len(args) < 1 {
		fmt.Printf("Usage: %s <numbers...>\n", os.Args[0])
		os.Exit(1)
	}

	var numbers []int
	for _, arg := range args {
		num, err := strconv.Atoi(arg)
		if err != nil {
			fmt.Printf("Error: '%s' is not a valid integer\n", arg)
			os.Exit(1)
		}
		numbers = append(numbers, num)
	}

	// Check for duplicates
	seen := make(map[int]bool)
	for _, num := range numbers {
		if seen[num] {
			fmt.Printf("Error: duplicate number %d\n", num)
			os.Exit(1)
		}
		seen[num] = true
	}

	ops, result := solver.SolvePushSwap(numbers)
	
	fmt.Printf("Operations: %d\n", len(ops))
	fmt.Printf("Result: %v\n", result)
	
	// Check if sorted
	for i := 1; i < len(result); i++ {
		if result[i] < result[i-1] {
			fmt.Printf("❌ Not sorted\n")
			os.Exit(1)
		}
	}
	fmt.Printf("✅ Sorted\n")
}
