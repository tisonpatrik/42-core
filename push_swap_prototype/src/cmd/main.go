package main

import (
	"bufio"
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

func main() {
	var numbers []int
	
	if len(os.Args) > 1 {
		// Read from command line arguments
		numbers = make([]int, len(os.Args)-1)
		for i, arg := range os.Args[1:] {
			num, _ := strconv.Atoi(arg)
			numbers[i] = num
		}
	} else {
		// Read from stdin
		scanner := bufio.NewScanner(os.Stdin)
		scanner.Scan()
		line := scanner.Text()
		
		parts := strings.Fields(line)
		numbers = make([]int, len(parts))
		for i, part := range parts {
			num, _ := strconv.Atoi(part)
			numbers[i] = num
		}
	}
	
	ps := ops.InitData(numbers)
	solver.SolvePushSwap(ps)
	
	for _, op := range ps.OpList {
		fmt.Println(OpToString(op))
	}
}