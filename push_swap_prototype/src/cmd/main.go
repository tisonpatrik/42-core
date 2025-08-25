package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/solver"
	"strconv"
)

func main() {
	args := os.Args[1:]
	var numbers []int

	if len(args) < 1 {
		// No arguments provided, generate 100 random numbers
		fmt.Println("No arguments provided, generating 100 random numbers...")
				
		// Generate 100 unique random numbers from 1 to 100
		// numbers = GenerateRandomNumbers(100)
		numbers = []int{71, 17, 20, 22, 13, 76, 62, 63, 81, 9, 86, 98, 67, 72, 59, 87, 37, 43, 65, 12, 6, 29, 42, 89, 69, 39, 3, 16, 38, 79, 83, 57, 96, 30, 75, 68, 25, 80, 36, 85, 77, 33, 84, 70, 54, 55, 8, 18, 73, 53, 47, 44, 32, 46, 90, 40, 56, 19, 26, 50, 7, 60, 21, 15, 58, 88, 11, 27, 61, 94, 35, 100, 5, 34, 51, 64, 45, 2, 66, 1, 78, 31, 28, 49, 24, 4, 74, 97, 95, 82, 52, 14, 92, 41, 99, 10, 93, 23, 48, 91}


	} else {
		// Parse command line arguments
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
