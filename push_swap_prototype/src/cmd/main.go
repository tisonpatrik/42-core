package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/solver"
	"push_swap_prototype/internal/stack"
)

func main() {
	file, err := os.Create("v2.txt")
	if err != nil {
		fmt.Printf("Error creating file: %v\n", err)
		return
	}
	defer file.Close()

	fmt.Fprintln(file, "Run\tIsSorted\tOpCount")

	for i := 1; i <= 1000; i++ {
		numbers := GenerateRandomNumbers(500)

		ps := ops.InitData(numbers)
		solver.SolvePushSwap(ps)
		res := Validate(numbers, ps.OpList)
		if !res.OK {
			fmt.Printf("INVALID: %v (at op %d)\n", res.Error, res.ErrorIndex)
			fmt.Printf("Input numbers: %v\n", numbers)
			fmt.Print("Stack A: ")
			stack.PrintStack(ps.A, "A")
			fmt.Print("Stack B: ")
			stack.PrintStack(ps.B, "B")
			panic("Validation failed - see above for details")
		}
		opCount := len(ps.OpList)

		fmt.Fprintf(file, "%d\n", opCount)

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