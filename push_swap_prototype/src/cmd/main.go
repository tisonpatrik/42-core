package main

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/ops"
	"push_swap_prototype/internal/solver"
	"strconv"
	"strings"
)

// func main() {
// 	file, err := os.Create("refactored.txt")
// 	if err != nil {
// 		fmt.Printf("Error creating file: %v\n", err)
// 		return
// 	}
// 	defer file.Close()

// 	fmt.Fprintln(file, "Run\tIsSorted\tOpCount")

// 	for i := 1; i <= 1000; i++ {
// 		numbers := GenerateRandomNumbers(500)

// 		ps := ops.InitData(numbers)
// 		solver.SolvePushSwap(ps)
// 		res := Validate(numbers, ps.OpList)
// 		if !res.OK {
// 			fmt.Printf("INVALID: %v (at op %d)\n", res.Error, res.ErrorIndex)
// 			fmt.Printf("Input numbers: %v\n", numbers)
// 			fmt.Print("Stack A: ")
// 			stack.PrintStack(ps.A, "A")
// 			fmt.Print("Stack B: ")
// 			stack.PrintStack(ps.B, "B")
// 			panic("Validation failed - see above for details")
// 		}
// 		opCount := len(ps.OpList)

// 		fmt.Fprintf(file, "%d\n", opCount)

// 		if i%100 == 0 {
// 			fmt.Printf("Completed %d runs...\n", i)
// 		}
// 	}

// 	fmt.Println("Completed 1000 runs. Results saved to refactored.txt")
// }

// parseString parses a space-separated string of numbers
func parseString(input string) ([]int, error) {
	parts := strings.Fields(input)
	numbers := make([]int, len(parts))
	
	for i, part := range parts {
		num, err := strconv.Atoi(part)
		if err != nil {
			return nil, fmt.Errorf("invalid number '%s'", part)
		}
		numbers[i] = num
	}
	
	return numbers, nil
}

// parseArguments handles command line argument parsing
func parseArguments() []int {
	if len(os.Args) <= 1 {
		return nil
	}
	
	if len(os.Args) == 2 {
		// Single string input (like from launch.json)
		numbers, err := parseString(os.Args[1])
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error: %v\n", err)
			os.Exit(1)
		}
		return numbers
	}
	
	// Multiple command line arguments
	numbers := make([]int, len(os.Args)-1)
	for i, arg := range os.Args[1:] {
		num, err := strconv.Atoi(arg)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error: invalid number '%s'\n", arg)
			os.Exit(1)
		}
		numbers[i] = num
	}
	return numbers
}

func main() {
	numbers := parseArguments()
	
	ps := ops.InitData(numbers)
	solver.SolvePushSwap(ps)
	
	for _, op := range ps.OpList {
		fmt.Println(OpToString(op))
	}
}