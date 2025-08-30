package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/solver"
)

func main() {
	// Create/open file for writing
	file, err := os.Create("v2.txt")
	if err != nil {
		fmt.Printf("Error creating file: %v\n", err)
		return
	}
	defer file.Close()

	// Write header
	fmt.Fprintln(file, "Run\tIsSorted\tOpCount")

	// Run 1000 times
	for i := 1; i <= 1000; i++ {
		numbers := GenerateRandomNumbers(500)

		ps := ops.InitData(numbers)
		solver.SolvePushSwap(ps)

		opCount := len(ps.OpList)

		// Write results to file
		fmt.Fprintf(file, "%d\n", opCount)

		// Also print to console every 100 runs for progress tracking
		if i%100 == 0 {
			fmt.Printf("Completed %d runs...\n", i)
		}
	}

	fmt.Println("Completed 1000 runs. Results saved to v2.txt")
}

// func main() {
// 	numbers := GenerateRandomNumbers(500)
// 	ps := ops.InitData(numbers)
// 	solver.SolvePushSwap(ps)
// 	stack.PrintStack(ps.A, "A")
// 	fmt.Println(stack.IsSorted(ps.A))
// 	fmt.Println(stack.IsEmpty(ps.B))
// 	fmt.Println(len(ps.OpList))

// }